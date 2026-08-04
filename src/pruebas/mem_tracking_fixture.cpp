#include <sstream>

#include "catch_amalgamated.hpp"
#include "memplumber.h"
#include "mem_tracking_fixture.hpp"

static unsigned int leakedGlobal = 0;

static int hayLeak()
{
    size_t leakCount = 0;
    uint64_t leakSize = 0;
    MemPlumber::memLeakCheck(leakCount, leakSize, false);
    return static_cast<int>(leakSize);
}

MemTrackingFixture::~MemTrackingFixture()
{
    MemTrackingFixture::checkSiActivo(false);
}

void MemTrackingFixture::checkSiActivo(bool report)
{
    if (!trackingActivo)
        return;

    trackingActivo = false;
    const int leaked = hayLeak() - leakedGlobal;
    MemPlumber::stop();

    if (leaked)
    {
        leakedGlobal += leaked;

        if (report)
        {
            std::ostringstream mensaje;
            mensaje << "Se perdieron " << leaked << " bytes";
            FAIL_CHECK(mensaje.str());
        }
    }
}

MemTrackingFixture::MemTrackingFixture()
{
    MemPlumber::start(false);
    trackingActivo = true;
}
