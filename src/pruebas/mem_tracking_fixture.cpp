#include <sstream>

#include "catch_amalgamated.hpp"
#include "func_aux.hpp"
#include "mem_tracking_fixture.hpp"

MemTrackingFixture::~MemTrackingFixture()
{
    if (!trackingActivo)
        return;

    const int leaked = FrameworkA1::hayLeak();
    FrameworkA1::detenerMemTracking();

    if (leaked != 0)
    {
        std::ostringstream mensaje;
        mensaje << "Se perdieron " << leaked << " bytes";
        FAIL_CHECK(mensaje.str());
    }
}

void MemTrackingFixture::comenzarTracking()
{
    FrameworkA1::comenzarMemTracking();
    trackingActivo = true;
}
