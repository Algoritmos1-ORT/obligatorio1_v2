#include <sstream>
#include "catch_amalgamated.hpp"
#include "ejercicios/listas.hpp"
#include "func_aux.hpp"

TEST_CASE("PruebaInvertirParcial cases", "[PruebaInvertirParcial][file:listas]")
{
    auto check = [](const char *inputLista, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *copiaLista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *resultado = invertirParcial(lista);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista, copiaLista);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input list");

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(copiaLista);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("(1) -> ()") { check("(1)", "()"); }
    SECTION("(1,2,3,4) -> (3,2,1)") { check("(1,2,3,4)", "(3,2,1)"); }
    SECTION("(-1,-2) -> (-1)") { check("(-1,-2)", "(-1)"); }
    SECTION("(1,2,3,4,3,2,1,0) -> (1,2,3,4,3,2,1)") { check("(1,2,3,4,3,2,1,0)", "(1,2,3,4,3,2,1)"); }
    SECTION("(1,2,3,4,3,2,1) -> (2,3,4,3,2,1)") { check("(1,2,3,4,3,2,1)", "(2,3,4,3,2,1)"); }
    SECTION("(1,1,1) -> (1,1)") { check("(1,1,1)", "(1,1)"); }
    SECTION("(0,1,2,3,4,5,6,7,8,9,10) -> (9,8,7,6,5,4,3,2,1,0)") { check("(0,1,2,3,4,5,6,7,8,9,10)", "(9,8,7,6,5,4,3,2,1,0)"); }
    SECTION("(0,1,0,5,0,1,0) -> (1,0,5,0,1,0)") { check("(0,1,0,5,0,1,0)", "(1,0,5,0,1,0)"); }
    SECTION("(8,9,5,1) -> (5,9,8)") { check("(8,9,5,1)", "(5,9,8)"); }
}

TEST_CASE("PruebaEliminarNesimoDesdeElFinal cases", "[PruebaEliminarNesimoDesdeElFinal][file:listas]")
{
    auto check = [](const char *inputLista, int n, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        eliminarNesimoDesdeElFinal(lista, n);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(lista, solucion);
        if (!ok)
        {
            char *got = FrameworkA1::serializar(lista);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(solucion);
    };

    SECTION("() n=50") { check("()", 50, "()"); }
    SECTION("(1) n=50") { check("(1)", 50, "(1)"); }
    SECTION("(1) n=1") { check("(1)", 1, "()"); }
    SECTION("(1,2,3,4,5) n=2") { check("(1,2,3,4,5)", 2, "(1,2,3,5)"); }
    SECTION("(1..10) n=10") { check("(1,2,3,4,5,6,7,8,9,10)", 10, "(2,3,4,5,6,7,8,9,10)"); }
    SECTION("(1..10) n=-5") { check("(1,2,3,4,5,6,7,8,9,10)", -5, "(1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("(1..10) n=0") { check("(1,2,3,4,5,6,7,8,9,10)", 0, "(1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("() n=1") { check("()", 1, "()"); }
    SECTION("(1..10) n=1") { check("(1,2,3,4,5,6,7,8,9,10)", 1, "(1,2,3,4,5,6,7,8,9)"); }
    SECTION("(111,2,3,4,55,6,7,88,99,10) n=2") { check("(111,2,3,4,55,6,7,88,99,10)", 2, "(111,2,3,4,55,6,7,88,10)"); }
    SECTION("(5, 6, 7, 8, 9) n=1") { check("(5, 6, 7, 8, 9)", 1, "(5, 6, 7, 8)"); }
}

TEST_CASE("PruebaListaOrdenadaInsertionSort cases", "[PruebaListaOrdenadaInsertionSort][file:listas]")
{
    auto check = [](const char *inputLista, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *copiaLista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *resultado = listaOrdenadaInsertionSort(lista);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista, copiaLista);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input list");

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(copiaLista);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("()") { check("()", "()"); }
    SECTION("(4)") { check("(4)", "(4)"); }
    SECTION("(1,1,1)") { check("(1,1,1)", "(1,1,1)"); }
    SECTION("(1,2,3)") { check("(1,2,3)", "(1,2,3)"); }
    SECTION("(1,4,2)") { check("(1,4,2)", "(1,2,4)"); }
    SECTION("(2,3,1)") { check("(2,3,1)", "(1,2,3)"); }
    SECTION("(-2,-3,-1)") { check("(-2,-3,-1)", "(-3,-2,-1)"); }
    SECTION("(1,1,4,1,3,8)") { check("(1,1,4,1,3,8)", "(1,1,1,3,4,8)"); }
    SECTION("(-2,3,1)") { check("(-2,3,1)", "(-2,1,3)"); }
    SECTION("(3,5,2,1,0)") { check("(3,5,2,1,0)", "(0,1,2,3,5)"); }
    SECTION("(9,2,2,5,1)") { check("(9,2,2,5,1)", "(1,2,2,5,9)"); }
    SECTION("(3,1,-1,1,0)") { check("(3,1,-1,1,0)", "(-1,0,1,1,3)"); }
    SECTION("(10..-2)") { check("(10,9,8,7,6,5,4,3,2,1,0,-1,-2)", "(-2,-1,0,1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("(7,3,7,10,-1,1,-6,0,-10,2,1,2)") { check("(7,3,7,10,-1,1,-6,0,-10,2,1,2)", "(-10,-6,-1,0,1,1,2,2,3,7,7,10)"); }
    SECTION("(10..-2)-duplicate") { check("(10,9,8,7,6,5,4,3,2,1,0,-1,-2)", "(-2,-1,0,1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("(8,7,5,2,-3,-1)") { check("(8,7,5,2,-3,-1)", "(-3,-1,2,5,7,8)"); }
    SECTION("(1,2,0,10,3,4)") { check("(1,2,0,10,3,4)", "(0,1,2,3,4,10)"); }
    SECTION("(1,2,4,3)") { check("(1,2,4,3)", "(1,2,3,4)"); }
    SECTION("(-2,0,3,1,1)") { check("(-2,0,3,1,1)", "(-2,0,1,1,3)"); }
}

TEST_CASE("PruebaListaOrdenadaSelectionSort cases", "[PruebaListaOrdenadaSelectionSort][file:listas]")
{
    auto check = [](const char *inputLista, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *resultado = lista;
        listaOrdenadaSelectionSort(resultado);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }

        FrameworkA1::destruir(resultado);
        FrameworkA1::destruir(solucion);
    };

    SECTION("()") { check("()", "()"); }
    SECTION("(4)") { check("(4)", "(4)"); }
    SECTION("(1,1,1)") { check("(1,1,1)", "(1,1,1)"); }
    SECTION("(1,2,3)") { check("(1,2,3)", "(1,2,3)"); }
    SECTION("(1,4,2)") { check("(1,4,2)", "(1,2,4)"); }
    SECTION("(2,3,1)") { check("(2,3,1)", "(1,2,3)"); }
    SECTION("(-2,-3,-1)") { check("(-2,-3,-1)", "(-3,-2,-1)"); }
    SECTION("(1,1,4,1,3,8)") { check("(1,1,4,1,3,8)", "(1,1,1,3,4,8)"); }
    SECTION("(-2,3,1)") { check("(-2,3,1)", "(-2,1,3)"); }
    SECTION("(3,5,2,1,0)") { check("(3,5,2,1,0)", "(0,1,2,3,5)"); }
    SECTION("(9,2,2,5,1)") { check("(9,2,2,5,1)", "(1,2,2,5,9)"); }
    SECTION("(3,1,-1,1,0)") { check("(3,1,-1,1,0)", "(-1,0,1,1,3)"); }
    SECTION("(10..-2)") { check("(10,9,8,7,6,5,4,3,2,1,0,-1,-2)", "(-2,-1,0,1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("(7,3,7,10,-1,1,-6,0,-10,2,1,2)") { check("(7,3,7,10,-1,1,-6,0,-10,2,1,2)", "(-10,-6,-1,0,1,1,2,2,3,7,7,10)"); }
    SECTION("(10..-2)-duplicate") { check("(10,9,8,7,6,5,4,3,2,1,0,-1,-2)", "(-2,-1,0,1,2,3,4,5,6,7,8,9,10)"); }
    SECTION("(8,7,5,2,-3,-1)") { check("(8,7,5,2,-3,-1)", "(-3,-1,2,5,7,8)"); }
    SECTION("(1,2,0,10,3,4)") { check("(1,2,0,10,3,4)", "(0,1,2,3,4,10)"); }
    SECTION("(1,2,4,3)") { check("(1,2,4,3)", "(1,2,3,4)"); }
    SECTION("(-2,0,3,1,1)") { check("(-2,0,3,1,1)", "(-2,0,1,1,3)"); }
}

TEST_CASE("PruebaIntercalarIter cases", "[PruebaIntercalarIter][file:listas]")
{
    auto check = [](const char *inputLista1, const char *inputLista2, const char *expected)
    {
        int largo1;
        NodoLista *lista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        int largo2;
        NodoLista *lista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *copiaLista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        NodoLista *copiaLista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *resultado = intercalarIter(lista1, lista2);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista1, copiaLista1) && FrameworkA1::sonIgualesDatosForma(lista2, copiaLista2);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista1) && !FrameworkA1::compartenMemoria(resultado, lista2);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input lists");

        FrameworkA1::destruir(lista1);
        FrameworkA1::destruir(lista2);
        FrameworkA1::destruir(copiaLista1);
        FrameworkA1::destruir(copiaLista2);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("() and ()") { check("()", "()", "()"); }
    SECTION("(1) and ()") { check("(1)", "()", "(1)"); }
    SECTION("(1) and (2)") { check("(1)", "(2)", "(1,2)"); }
    SECTION("(1,3,5,7,9) and (2,4,6,8)") { check("(1,3,5,7,9)", "(2,4,6,8)", "(1,2,3,4,5,6,7,8,9)"); }
    SECTION("(1,3,5,7,9,9) and (2,2,4,6,8)") { check("(1,3,5,7,9,9)", "(2,2,4,6,8)", "(1,2,2,3,4,5,6,7,8,9,9)"); }
    SECTION("(100,200,300,400) and same") { check("(100,200,300,400)", "(100,200,300,400)", "(100,100,200,200,300,300,400,400)"); }
    SECTION("() and (-1,0,1,5)") { check("()", "(-1,0,1,5)", "(-1,0,1,5)"); }
    SECTION("(19,24,233,2344) and (-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)") { check("(19,24,233,2344)", "(-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)", "(-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12,19,24,233,2344)"); }
    SECTION("(-1,-1,-1) and (-1,-1,-1,-1)") { check("(-1,-1,-1)", "(-1,-1,-1,-1)", "(-1,-1,-1,-1,-1,-1,-1)"); }
    SECTION("(-4,-1,0,5,7,10,12) and (0,1,1)") { check("(-4,-1,0,5,7,10,12)", "(0,1,1)", "(-4,-1,0,0,1,1,5,7,10,12)"); }
    SECTION("(2,2) and (2,2)") { check("(2,2)", "(2,2)", "(2,2,2,2)"); }
}

TEST_CASE("PruebaIntercalarRec cases", "[PruebaIntercalarRec][file:listas]")
{
    auto check = [](const char *inputLista1, const char *inputLista2, const char *expected)
    {
        int largo1;
        NodoLista *lista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        int largo2;
        NodoLista *lista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *copiaLista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        NodoLista *copiaLista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *resultado = intercalarRec(lista1, lista2);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista1, copiaLista1) && FrameworkA1::sonIgualesDatosForma(lista2, copiaLista2);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista1) && !FrameworkA1::compartenMemoria(resultado, lista2);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input lists");

        FrameworkA1::destruir(lista1);
        FrameworkA1::destruir(lista2);
        FrameworkA1::destruir(copiaLista1);
        FrameworkA1::destruir(copiaLista2);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("() and ()") { check("()", "()", "()"); }
    SECTION("(1) and ()") { check("(1)", "()", "(1)"); }
    SECTION("(1) and (2)") { check("(1)", "(2)", "(1,2)"); }
    SECTION("(1,3,5,7,9) and (2,4,6,8)") { check("(1,3,5,7,9)", "(2,4,6,8)", "(1,2,3,4,5,6,7,8,9)"); }
    SECTION("(1,3,5,7,9,9) and (2,2,4,6,8)") { check("(1,3,5,7,9,9)", "(2,2,4,6,8)", "(1,2,2,3,4,5,6,7,8,9,9)"); }
    SECTION("(100,200,300,400) and same") { check("(100,200,300,400)", "(100,200,300,400)", "(100,100,200,200,300,300,400,400)"); }
    SECTION("() and (-1,0,1,5)") { check("()", "(-1,0,1,5)", "(-1,0,1,5)"); }
    SECTION("(19,24,233,2344) and (-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)") { check("(19,24,233,2344)", "(-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)", "(-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12,19,24,233,2344)"); }
    SECTION("(-1,-1,-1) and (-1,-1,-1,-1)") { check("(-1,-1,-1)", "(-1,-1,-1,-1)", "(-1,-1,-1,-1,-1,-1,-1)"); }
    SECTION("(-4,-1,0,5,7,10,12) and (0,1,1)") { check("(-4,-1,0,5,7,10,12)", "(0,1,1)", "(-4,-1,0,0,1,1,5,7,10,12)"); }
    SECTION("(2,2) and (2,2)") { check("(2,2)", "(2,2)", "(2,2,2,2)"); }
}

TEST_CASE("PruebaInsComFin cases", "[PruebaInsComFin][file:listas]")
{
    auto check = [](const char *inputLista, int n, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *copiaLista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *resultado = insComFin(lista, n);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista, copiaLista);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input list");

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(copiaLista);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("(1,2,1) x=0") { check("(1,2,1)", 0, "(0,1,2,1,0)"); }
    SECTION("(1,2,3,4) x=5") { check("(1,2,3,4)", 5, "(5,4,3,2,1,5)"); }
    SECTION("(5) x=4") { check("(5)", 4, "(4,5,4)"); }
    SECTION("() x=4") { check("()", 4, "(4,4)"); }
    SECTION("(5,4,3,2,1,2,3,4,5) x=6") { check("(5,4,3,2,1,2,3,4,5)", 6, "(6,5,4,3,2,1,2,3,4,5,6)"); }
    SECTION("(1,1,1,1,1) x=1") { check("(1,1,1,1,1)", 1, "(1,1,1,1,1,1,1)"); }
    SECTION("(3,2,1) x=0") { check("(3,2,1)", 0, "(0,1,2,3,0)"); }
    SECTION("(9,5,6,1,2,4,8,9,5,55,2) x=33") { check("(9,5,6,1,2,4,8,9,5,55,2)", 33, "(33,2,55,5,9,8,4,2,1,6,5,9,33)"); }
    SECTION("(1,2,3,4,5) x=3") { check("(1,2,3,4,5)", 3, "(3,5,4,3,2,1,3)"); }
    SECTION("(9,5,1,7,5,3) x=1000") { check("(9,5,1,7,5,3)", 1000, "(1000,3,5,7,1,5,9,1000)"); }
}

TEST_CASE("PruebaEXOR cases", "[PruebaEXOR][file:listas]")
{
    auto check = [](const char *inputLista1, const char *inputLista2, const char *expected)
    {
        int largo1;
        NodoLista *lista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        int largo2;
        NodoLista *lista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *copiaLista1 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista1, largo1);
        NodoLista *copiaLista2 = (NodoLista *)FrameworkA1::parsearColeccion(inputLista2, largo2);
        NodoLista *resultado = exor(lista1, lista2);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(resultado, solucion);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista1, copiaLista1) && FrameworkA1::sonIgualesDatosForma(lista2, copiaLista2);
        bool noComparteMemoria = !FrameworkA1::compartenMemoria(resultado, lista1) && !FrameworkA1::compartenMemoria(resultado, lista2);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(resultado);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");
        if (!noComparteMemoria)
            FAIL("Result shares memory with input lists");

        FrameworkA1::destruir(lista1);
        FrameworkA1::destruir(lista2);
        FrameworkA1::destruir(copiaLista1);
        FrameworkA1::destruir(copiaLista2);
        FrameworkA1::destruir(solucion);
        FrameworkA1::destruir(resultado);
    };

    SECTION("(100,200,300,400) xor same") { check("(100,200,300,400)", "(100,200,300,400)", "()"); }
    SECTION("(1,2,3,4) xor (2,3,5,7)") { check("(1,2,3,4)", "(2,3,5,7)", "(1,4,5,7)"); }
    SECTION("() xor ()") { check("()", "()", "()"); }
    SECTION("() xor (-1,0,1,5)") { check("()", "(-1,0,1,5)", "(-1,0,1,5)"); }
    SECTION("(19,24,233,2344) xor (-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)") { check("(19,24,233,2344)", "(-1222,-129,-12,0,0,0,0,0,0,1,2,3,4,12)", "(-1222,-129,-12,0,1,2,3,4,12,19,24,233,2344)"); }
    SECTION("(-9,-5,-1) xor (1,6,8,9)") { check("(-9,-5,-1)", "(1,6,8,9)", "(-9,-5,-1,1,6,8,9)"); }
    SECTION("(0,2,3) xor (0,1,2,5,7,9,11)") { check("(0,2,3)", "(0,1,2,5,7,9,11)", "(1,3,5,7,9,11)"); }
    SECTION("(1,2,2,2,3,4) xor (1,3,5,7)") { check("(1,2,2,2,3,4)", "(1,3,5,7)", "(2,4,5,7)"); }
    SECTION("(100,200,300,400) xor (100,200,200,300,400)") { check("(100,200,300,400)", "(100,200,200,300,400)", "()"); }
    SECTION("(1,1,2,5) xor (2,3,3,5)") { check("(1,1,2,5)", "(2,3,3,5)", "(1,3)"); }
    SECTION("(-1,1,2,5,5) xor (2,3,3,5,5,5,7,7)") { check("(-1,1,2,5,5)", "(2,3,3,5,5,5,7,7)", "(-1,1,3,7)"); }
    SECTION("(-1,1,2,5,5) xor (2,3,3,5,5,5)") { check("(-1,1,2,5,5)", "(2,3,3,5,5,5)", "(-1,1,3)"); }
    SECTION("(-1,1,2,5,5) xor (2,3,3,5)") { check("(-1,1,2,5,5)", "(2,3,3,5)", "(-1,1,3)"); }
}

TEST_CASE("PruebaEliminarDuplicadosListaOrdenadaDos cases", "[PruebaEliminarDuplicadosListaOrdenadaDos][file:listas]")
{
    auto check = [](const char *inputLista, const char *expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        eliminarDuplicadosListaOrdenadaDos(lista);
        int largoSolucion;
        NodoLista *solucion = (NodoLista *)FrameworkA1::parsearColeccion(expected, largoSolucion);

        bool ok = FrameworkA1::sonIgualesDatosForma(lista, solucion);
        if (!ok)
        {
            char *got = FrameworkA1::serializar(lista);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(solucion);
    };

    SECTION("(100,100,200,200,300,300,400,400)") { check("(100,100,200,200,300,300,400,400)", "()"); }
    SECTION("()") { check("()", "()"); }
    SECTION("(-1,0,1,1,1,1,5,5,5,5,5)") { check("(-1,0,1,1,1,1,5,5,5,5,5)", "(-1,0)"); }
    SECTION("(-5,-5,-4,0,2,3,5,6,7,9,10,15,50,65,78,150)") { check("(-5,-5,-4,0,2,3,5,6,7,9,10,15,50,65,78,150)", "(-4,0,2,3,5,6,7,9,10,15,50,65,78,150)"); }
    SECTION("(0,1,2,2,3,3,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,10)") { check("(0,1,2,2,3,3,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,10)", "(0,1,9,10)"); }
    SECTION("(0,0,0,1,1,1)") { check("(0,0,0,1,1,1)", "()"); }
    SECTION("(1,1,2,2,2,3,3,3,3,5)") { check("(1,1,2,2,2,3,3,3,3,5)", "(5)"); }
    SECTION("(5)") { check("(5)", "(5)"); }
    SECTION("(-1,0,1)") { check("(-1,0,1)", "(-1,0,1)"); }
    SECTION("(0,1,1,2,2,2,3,3,3,3,4,4,4,4,4)") { check("(0,1,1,2,2,2,3,3,3,3,4,4,4,4,4)", "(0)"); }
}

TEST_CASE("PruebaPalindromo cases", "[PruebaPalindromo][file:listas]")
{
    auto check = [](const char *inputLista, bool expected)
    {
        int largo;
        NodoLista *lista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);
        NodoLista *copiaLista = (NodoLista *)FrameworkA1::parsearColeccion(inputLista, largo);

        bool resultado = palindromo(lista);
        bool ok = resultado == expected;
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(lista, copiaLista);

        if (!ok)
        {
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << resultado;
            FAIL(oss.str());
        }
        if (!parametrosNoModificados)
            FAIL("Function modified input parameters");

        FrameworkA1::destruir(lista);
        FrameworkA1::destruir(copiaLista);
    };

    SECTION("(1,0,1)") { check("(1,0,1)", true); }
    SECTION("()") { check("()", true); }
    SECTION("(1)") { check("(1)", true); }
    SECTION("(1,1)") { check("(1,1)", true); }
    SECTION("(1,2)") { check("(1,2)", false); }
    SECTION("(1,2,3)") { check("(1,2,3)", false); }
    SECTION("(1,2,3,4,3,3,1)") { check("(1,2,3,4,3,3,1)", false); }
    SECTION("(1,2,3,4,3,2,1)") { check("(1,2,3,4,3,2,1)", true); }
    SECTION("(1,2,3,4,3,2)") { check("(1,2,3,4,3,2)", false); }
    SECTION("(1,2,3,3,2,1)") { check("(1,2,3,3,2,1)", true); }
    SECTION("(1,1,1,1,1,1,1)") { check("(1,1,1,1,1,1,1)", true); }
}

TEST_CASE("PruebaEliminarSecuencia cases", "[PruebaEliminarSecuencia][file:listas]")
{
    auto check = [](const char *inputListaOriginal, const char *inputSecuenciaAEliminar, const char *expected)
    {
        int largo;
        NodoLista *listaOriginal = (NodoLista *)FrameworkA1::parsearColeccion(inputListaOriginal, largo);
        NodoLista *secuenciaAEliminar = (NodoLista *)FrameworkA1::parsearColeccion(inputSecuenciaAEliminar, largo);
        NodoLista *copiaSecuenciaAEliminar = (NodoLista *)FrameworkA1::parsearColeccion(inputSecuenciaAEliminar, largo);
        NodoLista *resultadoEsperado = (NodoLista *)FrameworkA1::parsearColeccion(expected, largo);

        eliminarSecuencia(listaOriginal, secuenciaAEliminar);
        bool ok = FrameworkA1::sonIgualesDatosForma(listaOriginal, resultadoEsperado);
        bool parametrosNoModificados = FrameworkA1::sonIgualesDatosForma(secuenciaAEliminar, copiaSecuenciaAEliminar);

        if (!ok)
        {
            char *got = FrameworkA1::serializar(listaOriginal);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }
        if (!parametrosNoModificados)
            FAIL("Function modified the sequence to remove");

        FrameworkA1::destruir(listaOriginal);
        FrameworkA1::destruir(secuenciaAEliminar);
        FrameworkA1::destruir(copiaSecuenciaAEliminar);
        FrameworkA1::destruir(resultadoEsperado);
    };

    SECTION("() remove ()") { check("()", "()", "()"); }
    SECTION("(1,2,3,4,5,6,7,8,9,0) remove (2,3,4)") { check("(1,2,3,4,5,6,7,8,9,0)", "(2,3,4)", "(1,5,6,7,8,9,0)"); }
    SECTION("(1,2,3,4,5,6,7,8,9,0) remove (2,4,5,6)") { check("(1,2,3,4,5,6,7,8,9,0)", "(2,4,5,6)", "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("(1,2,3,4,5,6,7,8,9,0) remove ()") { check("(1,2,3,4,5,6,7,8,9,0)", "()", "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("() remove (1,2,3,4,5,6,7,8,9,0)") { check("()", "(1,2,3,4,5,6,7,8,9,0)", "()"); }
    SECTION("(1,2,3,4,5,6,7,8,9,0) remove (1,2)") { check("(1,2,3,4,5,6,7,8,9,0)", "(1,2)", "(3,4,5,6,7,8,9,0)"); }
    SECTION("(1,2,3,4,5,6,7,8,9,0) remove (9,0)") { check("(1,2,3,4,5,6,7,8,9,0)", "(9,0)", "(1,2,3,4,5,6,7,8)"); }
    SECTION("(1,2,1,2,4,5,6,7,8,9,0) remove (1,2)") { check("(1,2,1,2,4,5,6,7,8,9,0)", "(1,2)", "(1,2,4,5,6,7,8,9,0)"); }
    SECTION("(4,2,1,2,5,6,4,2,2,1) remove (4,2,2)") { check("(4,2,1,2,5,6,4,2,2,1)", "(4,2,2)", "(4,2,1,2,5,6,1)"); }
    SECTION("(4,3,2,1,4,3,2,1) remove (4,3,2,1,0)") { check("(4,3,2,1,4,3,2,1)", "(4,3,2,1,0)", "(4,3,2,1,4,3,2,1)"); }
}

TEST_CASE("PruebaMoverNodo cases", "[PruebaMoverNodo][file:listas]")
{
    auto check = [](const char *inputListaOriginal, unsigned int inicial, unsigned int final, const char *expected)
    {
        int largo;
        NodoLista *listaOriginal = (NodoLista *)FrameworkA1::parsearColeccion(inputListaOriginal, largo);
        NodoLista *resultadoEsperado = (NodoLista *)FrameworkA1::parsearColeccion(expected, largo);

        moverNodo(listaOriginal, inicial, final);
        bool ok = FrameworkA1::sonIgualesDatosForma(listaOriginal, resultadoEsperado);
        if (!ok)
        {
            char *got = FrameworkA1::serializar(listaOriginal);
            std::ostringstream oss;
            oss << "Expected: " << expected << " Received: " << got;
            std::string msg = oss.str();
            delete[] got;
            FAIL(msg);
        }

        FrameworkA1::destruir(listaOriginal);
        FrameworkA1::destruir(resultadoEsperado);
    };

    SECTION("move 1->2") { check("(1,2,3,4,5,6,7,8,9,0)", 1, 2, "(2,1,3,4,5,6,7,8,9,0)"); }
    SECTION("move 1->5") { check("(1,2,3,4,5,6,7,8,9,0)", 1, 5, "(2,3,4,5,1,6,7,8,9,0)"); }
    SECTION("move 5->1") { check("(1,2,3,4,5,6,7,8,9,0)", 5, 1, "(5,1,2,3,4,6,7,8,9,0)"); }
    SECTION("move 1->1") { check("(1,2,3,4,5,6,7,8,9,0)", 1, 1, "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("move 3->11 invalid") { check("(1,2,3,4,5,6,7,8,9,0)", 3, 11, "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("move 3->7") { check("(1,2,3,4,5,6,7,8,9,0)", 3, 7, "(1,2,4,5,6,7,3,8,9,0)"); }
    SECTION("move 7->3") { check("(1,2,3,4,5,6,7,8,9,0)", 7, 3, "(1,2,7,3,4,5,6,8,9,0)"); }
    SECTION("move 12->2 invalid") { check("(1,2,3,4,5,6,7,8,9,0)", 12, 2, "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("move 10->9") { check("(1,2,3,4,5,6,7,8,9,0)", 10, 9, "(1,2,3,4,5,6,7,8,0,9)"); }
    SECTION("move 10->10") { check("(1,2,3,4,5,6,7,8,9,0)", 10, 10, "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("move 0->10 invalid") { check("(1,2,3,4,5,6,7,8,9,0)", 0, 10, "(1,2,3,4,5,6,7,8,9,0)"); }
    SECTION("move 10->0 invalid") { check("(1,2,3,4,5,6,7,8,9,0)", 10, 0, "(1,2,3,4,5,6,7,8,9,0)"); }
}
