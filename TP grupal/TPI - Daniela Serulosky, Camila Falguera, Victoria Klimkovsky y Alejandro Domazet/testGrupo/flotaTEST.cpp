#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

vector<viaje> fl = {{
                   medicion(1.7,puntoGps(2.5, 2.89997)),
                   medicion(1.5,puntoGps(2.5, 2.89996)),
                   medicion(1.9,puntoGps(2.5, 2.89998))},
                   {
                    medicion(2.5,puntoGps(2.5, 2.89996)),
                    medicion(2.6,puntoGps(2.5, 2.89997)),
                    medicion(2.7,puntoGps(2.5, 2.89998))},
                   {
                    medicion(0.5,puntoGps(2.5, 2.89996)),
                    medicion(0.6,puntoGps(2.5, 2.89997)),
                    medicion(0.7,puntoGps(2.5, 2.89998))},
                   };
//ahora entra a tiempoMinimo
TEST(flotaTotalTEST, todosAntesDeFranjaNuevo){
    EXPECT_EQ(flota(fl,3.0,5.0),0);
}


//ahora entra a tiempoMinimo
TEST(flotaTotalTEST, AlgunosAdentroNuevo){
    EXPECT_EQ(flota(fl, 1.8,2.55),2);
}

TEST(flotaTotalTEST, TodosAdentro){
    EXPECT_EQ(flota(fl, 0.4,2.8),3);
}

//todos estan despues de la franja
TEST(flotaTotalTEST, todosDespuesDeFranja){
    EXPECT_EQ(flota(fl, 0.2,0.4),0);
}