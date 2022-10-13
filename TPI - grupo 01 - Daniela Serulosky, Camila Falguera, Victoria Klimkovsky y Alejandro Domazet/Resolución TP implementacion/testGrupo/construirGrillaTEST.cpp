#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(construirGrillaTEST, nombresCorrectosDistanciaParNParMImparArgExtendido){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                  make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                  make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                  make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                  make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                  make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
                  };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_EQ(contenidoEn(g, gres), true);
    EXPECT_EQ(contenidoEn(gres, g), true);
}



TEST(construirGrillaTEST, grillaNxN){

    int n = 3;
    int m = 3;

    gps esq1 = puntoGps(20.0,10.0);
    gps esq2 = puntoGps(-40.0,40.0);

    grilla gres = {make_tuple(puntoGps(20.0,10.0), puntoGps(0.0,20.0), make_tuple(1,1)),
                   make_tuple(puntoGps(20.0,10.0), puntoGps(0.0,30.0), make_tuple(1,2)),
                   make_tuple(puntoGps(20.0,30.0), puntoGps(0.0,40.0), make_tuple(1,3)),
                   make_tuple(puntoGps(0.0,10.0), puntoGps(-20.0,20.0), make_tuple(2,1)),
                   make_tuple(puntoGps(0.0,30.0), puntoGps(-20.0,30.0), make_tuple(2,2)),
                   make_tuple(puntoGps(0.0,30.0), puntoGps(-20.0,40.0), make_tuple(2,3)),
                   make_tuple(puntoGps(-20.0,10.0), puntoGps(-40.0,20.0), make_tuple(3,1)),
                   make_tuple(puntoGps(-20.0,20.0), puntoGps(-40.0,30.0), make_tuple(3,2)),
                   make_tuple(puntoGps(-20.0,30.0), puntoGps(-40.0,40.0), make_tuple(3,3))
    };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_EQ(contenidoEn(g, gres), true);
    EXPECT_EQ(contenidoEn(gres, g), true);
}