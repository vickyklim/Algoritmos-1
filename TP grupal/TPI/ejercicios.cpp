#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {

    tiempo tmax = obtenerTiempo(v[0]); // cte
    tiempo tmin = obtenerTiempo(v[0]); // cte

    for(int i=0 ; i<v.size() ; i++){ // n + cte
        if(obtenerTiempo(v[i]) > tmax){ // n + cte
            tmax = obtenerTiempo(v[i]); // n + cte
        }
        if(obtenerTiempo(v[i]) < tmin){ // n + cte
            tmin = obtenerTiempo(v[i]); // n + cte
        }

    }
    tiempo t = tmax - tmin; // n + cte

    // g(n) = n + cte
    // O(n)

    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/

distancia distanciaTotal(viaje v) {
    distancia d = 0; // cte
    viaje ordenado = bubbleSort(v); // n^2 + cte
    for(int i=0 ; i < ordenado.size()-1 ; i++){ // n^2 + n + cte
        d +=  distEnKM(obtenerPosicion(ordenado[i+1]), obtenerPosicion(ordenado[i])); // n^2 + n + cte
    }

    // g(n) = n^2 + n + cte
    // O(n^2)

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/

bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    viaje ordenado = bubbleSort(v);
    for(int i=0; i<ordenado.size()-1;i++){
        if (velocidad(ordenado[i],ordenado[i+1])>80){
            resp = true;
        }
    }
    return resp;
}


/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    for (int i=0; i<r.size();i++){ // n
        if (not(medicionCubierta(r[i], v, u))){ // n * m + cte
            resp.push_back(r[i]); // n * m + cte
        }
    }

    return resp;
}

// n = longitud del recorrido
// m = longitud del viaje
// g(n, m) = n * m + cte
// O(n * m)

/***************************************** EJERCICIO flota ***************************************/

int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    tiempo tmin = 0 ;
    tiempo tmax = 0 ;
    for(int i = 0; i< f.size(); i++) {
        tmin = encontrarMinimo(f[i]);
        tmax = encontrarMaximo(f[i]);
        if (not(tmax < t0 || tmin > tf)) {
            resp += 1;
        }
    }
    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp(n*m);
    for (int i=0; i < n*m; i++) {

        get<0>(get<2>(resp[i])) = i%n + 1; //nombre pos 1
        get<1>(get<2>(resp[i])) = i%m + 1; //nombre pos 2
        get<0>(get<0>(resp[i])) = latPosSupCelda(i%n + 1,esq1,esq2, n);// latPosSup
        get<1>(get<0>(resp[i])) = longPosSupCelda(i%m + 1,esq1,esq2, m); // longPosSup
        get<0>(get<1>(resp[i])) = latPosInfCelda((latPosSupCelda(i%n + 1,esq1,esq2, n)), esq1, esq2, n); // latPosInf
        get<1>(get<1>(resp[i])) = longPosInfCelda((longPosSupCelda(i%m + 1,esq1,esq2, m)), esq1, esq2, m); // longPosInf



    }

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/

int cantidadDeSaltos(grilla g, viaje v) {
    int resp=0;
    viaje ordenado = bubbleSort(v);
    for (int i = 0; i< ordenado.size()-1;i++){
        nombre actual = get<2>(asignarCelda(ordenado[i], g));
        nombre siguiente = get<2>(asignarCelda(ordenado[i+1], g));
        if (distanciaNombres(actual, siguiente) > 1.0){
            resp += 1;
        }
    }

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/

void corregirViaje(viaje& v, vector<tiempo> errores){
    for (int j=0; j<errores.size(); j++){
        for (int i=0; i<v.size(); i++){
            if (obtenerTiempo(v[i]) == errores[j] && obtenerTiempo(v[i]) == errores[j]){
                cambio((get<1>(v[i])), v, i, errores);
            }
        }
    }
}
