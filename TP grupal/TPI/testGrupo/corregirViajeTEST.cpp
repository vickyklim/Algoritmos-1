#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(corregirViajeTEST, errorAnterior){
    viaje v = {medicion(+1.3, puntoGps(37, 98)),
               medicion(+1.8, puntoGps(12, 24)),
               medicion(+23, puntoGps(18, 24)),
               medicion(1, puntoGps(-34.578941, -58.424878)),
               medicion(75, puntoGps(81, -50)),
               medicion(+1.5, puntoGps(30, 112))};

    viaje res = {medicion(+1.3, puntoGps(37, 98)),
                 medicion(+1.8, puntoGps(12, 24)),
                 medicion(+23, puntoGps(18, 24)),
                 medicion(+1, puntoGps(47.5, 77)),
                 medicion(75, puntoGps(81, -50)),
                 medicion(+1.5, puntoGps(30, 112))};
    vector<tiempo> errores = {1};


    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}


TEST(corregirViajeTEST, errorEnElMedio){
    viaje v = {medicion(+0, puntoGps(50, 10)),
               medicion(+10, puntoGps(20, 80)),
               medicion(+5, puntoGps(58, 12)),
               medicion(19, puntoGps(-34.578941, -58.424878)),
               medicion(100, puntoGps(71.65, -34.8752)),
               medicion(243, puntoGps(21.548, 25.78524))};

    viaje res = {medicion(+0, puntoGps(50, 10)),
                 medicion(+10, puntoGps(20, 80)),
                 medicion(+5, puntoGps(35, 45)),
                 medicion(19, puntoGps(-34.578941, -58.424878)),
                 medicion(100, puntoGps(71.65, -34.8752)),
                 medicion(243, puntoGps(21.548, 25.78524))};
    vector<tiempo> errores = {5};


    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}


TEST(corregirViajeTEST, erroresConsecutivos){
    viaje v = {medicion(100, puntoGps(88, 92)),
               medicion(400, puntoGps(40, 35)),
               medicion(300, puntoGps(-25.58, 12.548)),
               medicion(200, puntoGps(80, 70)),
               medicion(350, puntoGps(71.65, -34.8752)),
               medicion(600, puntoGps(28, 23)),
               medicion(500, puntoGps(32, 30))};

    viaje res = {medicion(100, puntoGps(88, 92)),
                 medicion(400, puntoGps(40, 35)),
                 medicion(300, puntoGps(60, 52.5)),
                 medicion(200, puntoGps(80, 70)),
                 medicion(350, puntoGps(50, 43.75)),
                 medicion(600, puntoGps(28, 23)),
                 medicion(500, puntoGps(32, 30))};
    vector<tiempo> errores = {350, 300};


    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, errorContenido) {
    viaje v = {medicion(20, puntoGps(20, -40)),
               medicion(40, puntoGps(30, -35)),
               medicion(60, puntoGps(-80, 35)),
               medicion(200, puntoGps(110, 5)),
               medicion(240, puntoGps(130, 15))};

    viaje res = {medicion(20, puntoGps(20, -40)),
                 medicion(40, puntoGps(30, -35)),
                 medicion(60, puntoGps(40, -30)),
                 medicion(200, puntoGps(110, 5)),
                 medicion(240, puntoGps(130, 15))};
    vector<tiempo> errores = {60};


    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, mayorConError) {
    viaje v = {medicion(20, puntoGps(20, -40)),
               medicion(40, puntoGps(30, -35)),
               medicion(60, puntoGps(-80, 35)),
               medicion(200, puntoGps(110, 5)),
               medicion(240, puntoGps(130, 15))};

    viaje res = {medicion(20, puntoGps(20, -40)),
                 medicion(40, puntoGps(30, -35)),
                 medicion(60, puntoGps(40, -30)),
                 medicion(200, puntoGps(110, 5)),
                 medicion(240, puntoGps(130, 15))};
    vector<tiempo> errores = {60};


    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}