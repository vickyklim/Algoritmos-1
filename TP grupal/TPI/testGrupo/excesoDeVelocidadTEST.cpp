#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

//ahora no esta ordenado
TEST(excesoDeVelocidadTEST, noSuperaLaVelocidadNuevo){
    viaje v = {medicion(0.0, P),
               medicion(unaHora*2, desviarPunto(P, 2000, 0)),
               medicion(unaHora, desviarPunto(P, 1000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}

//ahora no esta ordenado
TEST(excesoDeVelocidadTEST, superaLaVelocidadNuevo){
    viaje v = {medicion(0.0, P),
               medicion(unaHora*2, desviarPunto(P, 200000, 0)),
               medicion(unaHora, desviarPunto(P, 100000, 0))}; // 100 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}
