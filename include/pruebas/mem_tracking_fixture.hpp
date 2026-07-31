#pragma once

class MemTrackingFixture
{
public:
    MemTrackingFixture() = default;
    MemTrackingFixture(const MemTrackingFixture &) = delete;
    MemTrackingFixture &operator=(const MemTrackingFixture &) = delete;
    ~MemTrackingFixture();

    void comenzarTracking();

private:
    bool trackingActivo = false;
};
