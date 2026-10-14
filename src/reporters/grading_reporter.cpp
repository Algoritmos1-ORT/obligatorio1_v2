#include "catch_amalgamated.hpp"

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>

namespace {

class GradingReporter final : public Catch::StreamingReporterBase {
public:
    explicit GradingReporter(Catch::ReporterConfig&& config)
        : StreamingReporterBase(CATCH_MOVE(config)) {
        m_preferences.shouldRedirectStdOut = true;
    }

    static std::string getDescription() {
        return "Summarizes test cases grouped by exercise tag and benchmarks separately";
    }

    void testCaseStarting(Catch::TestCaseInfo const& info) override {
        StreamingReporterBase::testCaseStarting(info);
        m_sections.clear();
        m_failedOutsideSections = false;
    }

    void assertionEnded(Catch::AssertionStats const& stats) override {
        if (m_sectionStack.size() <= 1 && !stats.assertionResult.succeeded()) {
            m_failedOutsideSections = true;
        }
    }

    void sectionEnded(Catch::SectionStats const& stats) override {
        // The implicit TEST_CASE section is depth 1. Count each explicit
        // top-level section once, even when nested sections rerun it.
        if (m_sectionStack.size() == 2) {
            auto const& info = stats.sectionInfo;
            auto key = std::make_tuple(std::string(info.lineInfo.file),
                                       info.lineInfo.line, info.name);
            auto& failed = m_sections[key];
            failed = failed || !stats.assertions.allPassed();
        }
        StreamingReporterBase::sectionEnded(stats);
    }

    void testCaseEnded(Catch::TestCaseStats const& stats) override {
        const bool passed = stats.totals.testCases.passed == 1 &&
                            stats.totals.assertions.allPassed();
        if (!countBenchmark(*stats.testInfo, passed)) {
            auto& group = m_groups[groupKey(*stats.testInfo)];
            const auto failedSections = static_cast<std::size_t>(std::count_if(
                m_sections.begin(), m_sections.end(),
                [](auto const& section) { return section.second; }));
            group.passed = group.passed && passed;
            group.sections += m_sections.size();
            group.failedSections += failedSections;
            group.ungradableFailure = group.ungradableFailure ||
                m_failedOutsideSections || stats.totals.testCases.skipped > 0 ||
                (!passed && failedSections == 0);
        }
        StreamingReporterBase::testCaseEnded(stats);
    }

    void skipTest(Catch::TestCaseInfo const& info) override {
        // Selected tests skipped after aborting cannot receive passing credit.
        if (!countBenchmark(info, false)) {
            auto& group = m_groups[groupKey(info)];
            group.passed = false;
            group.ungradableFailure = true;
        }
    }

    void testRunEnded(Catch::TestRunStats const& stats) override {
        std::uint64_t passed = 0, partial = 0, failed = 0;
        for (auto const& entry : m_groups) {
            auto const& group = entry.second;
            if (group.passed) {
                ++passed;
            } else if (!group.ungradableFailure && group.failedSections > 0 &&
                       group.failedSections * 2 < group.sections) {
                ++partial;
            } else {
                ++failed;
            }
        }
        // Salida para batch: una linea con valores separados por coma, en este orden.
        m_stream << m_groups.size() << ','    // Grupos sin [benchmark], incluye memoria.
                 << passed << ','             // Grupos sin errores.
                 << partial << ','            // Errores en menos del 50% de secciones.
                 << failed << ','             // Errores desde el 50%, o que no pasan.
                 << m_benchmarks << ','       // Total de benchmarks.
                 << m_passedBenchmarks << '\n'; // Benchmarks que pasan.
        StreamingReporterBase::testRunEnded(stats);
    }

private:
    struct GroupStats {
        std::size_t sections = 0;
        std::size_t failedSections = 0;
        bool passed = true;
        bool ungradableFailure = false;
    };

    static std::string groupKey(Catch::TestCaseInfo const& info) {
        std::string candidate;
        std::size_t candidates = 0;
        for (auto const& tag : info.tags) {
            const auto name = static_cast<std::string>(tag.original);
            if (name.empty() || name == "memory" || name == "benchmark" ||
                name.compare(0, 5, "file:") == 0 ||
                name.front() == '!' || name.front() == '.') {
                continue;
            }
            // Prefer the exercise name used as a prefix of the TEST_CASE name;
            // tag order is irrelevant. A single ordinary tag also identifies it.
            if (info.name == name || info.name.compare(0, name.size() + 1,
                                                      name + " ") == 0) {
                return "tag:" + name;
            }
            candidate = name;
            ++candidates;
        }
        // Untagged or ambiguous cases stay independent.
        return candidates == 1 ? "tag:" + candidate : "case:" + info.name;
    }

    static bool hasTag(Catch::TestCaseInfo const& info, Catch::StringRef name) {
        return std::any_of(info.tags.begin(), info.tags.end(),
                           [name](Catch::Tag const& tag) {
                               return tag.original == name;
                           });
    }

    bool countBenchmark(Catch::TestCaseInfo const& info, bool passed) {
        const bool benchmark = hasTag(info, "benchmark");
        if (benchmark) {
            ++m_benchmarks;
            m_passedBenchmarks += passed;
        }
        return benchmark;
    }

    std::map<std::tuple<std::string, std::size_t, std::string>, bool> m_sections;
    bool m_failedOutsideSections = false;
    std::map<std::string, GroupStats> m_groups;
    std::uint64_t m_benchmarks = 0;
    std::uint64_t m_passedBenchmarks = 0;
};

} // namespace

CATCH_REGISTER_REPORTER("grading", GradingReporter)
