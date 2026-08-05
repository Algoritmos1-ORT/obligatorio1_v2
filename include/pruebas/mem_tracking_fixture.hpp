#pragma once

class MemTrackingFixture
{
public:
    MemTrackingFixture();
    MemTrackingFixture(const MemTrackingFixture &) = delete;
    MemTrackingFixture &operator=(const MemTrackingFixture &) = delete;
    ~MemTrackingFixture();

    void checkSiActivo(bool report = true);

private:
    bool trackingActivo = false;
};

template <typename Funcion>
void checkMemoriaEjecucion(Funcion funcion)
{
    MemTrackingFixture memTracking;
    funcion();
    memTracking.checkSiActivo();
}
