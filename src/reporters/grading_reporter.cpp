#include "catch_amalgamated.hpp"

#include <iomanip>
#include <string>

namespace {

class GradingReporter final : public Catch::StreamingReporterBase {
public:
    explicit GradingReporter(Catch::ReporterConfig&& config)
        : StreamingReporterBase(CATCH_MOVE(config)) {}

    static std::string getDescription() {
        return "Prints only the percentage of passing test cases";
    }

    void testRunEnded(Catch::TestRunStats const& stats) override {
        const auto total = stats.totals.testCases.total();
        const double percentage = total == 0
            ? 0.0
            : 100.0 * static_cast<double>(stats.totals.testCases.passed) /
                  static_cast<double>(total);

        m_stream << std::fixed << std::setprecision(2) << percentage << "%\n";
    }
};

} // namespace

CATCH_REGISTER_REPORTER("grading", GradingReporter)
