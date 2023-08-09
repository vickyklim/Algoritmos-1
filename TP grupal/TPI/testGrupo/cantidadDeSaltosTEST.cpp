#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTEST, saltosDiagonales){
    grilla g = construirGrilla(puntoGps(40.0,0.0),puntoGps(0,60.0), 2, 3);

    gps p1 = puntoGps(10, 10);
    gps p2 = puntoGps(30, 30);
    gps p3 = puntoGps(10, 50);
    gps p4 = puntoGps(10, 30);

    viaje v = {medicion(0, p1),
               medicion(3600, p2),
               medicion(7200, p3),
               medicion(10800, p4),};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, saltosDiagonalesDesordenados){
    grilla g = construirGrilla(puntoGps(40.0,0.0),puntoGps(0,60.0), 2, 3);

    gps p1 = puntoGps(10, 10);
    gps p2 = puntoGps(30, 30);
    gps p3 = puntoGps(10, 50);
    gps p4 = puntoGps(10, 30);

    viaje v = {
            medicion(3600, p2),
            medicion(10800, p4),
            medicion(0, p1),
            medicion(7200, p3),
            };

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}


TEST(cantidadDeSaltosTEST, saltoGrande){
    grilla g = construirGrilla(puntoGps(20.0,10.0),puntoGps(-40.0,40.0), 3, 3);

    gps p1 = puntoGps(-39, 31);
    gps p2 = puntoGps(-18, 32);
    gps p3 = puntoGps(3, 35);
    gps p4 = puntoGps(-38, 12);

    viaje v = {
            medicion(3600, p2),
            medicion(10800, p4),
            medicion(0, p1),
            medicion(7200, p3),
    };

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}