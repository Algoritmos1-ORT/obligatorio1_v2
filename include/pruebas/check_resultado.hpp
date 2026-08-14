#pragma once

#include "catch_amalgamated.hpp"

template <typename Resultado, typename Esperado, typename Serializar>
void checkResultadoSerializado(bool coincide, Resultado resultado, const Esperado &esperado, Serializar serializar)
{
    if (!coincide)
    {
        char *recibido = serializar(resultado);
        FAIL_CHECK("Esperado: " << esperado << " -- Recibido: " << recibido);
        delete[] recibido;
    }
    else
        CHECK(true);
}
