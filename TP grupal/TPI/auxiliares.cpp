#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;


const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

/*
void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

*/


void swap (viaje &v, tuple<tiempo,gps> &ant, tuple<tiempo,gps> &post){
    tuple<tiempo,gps> aux = ant; // n^2 + cte
    ant = post; // n^2 + cte
    post = aux; // n^2 + cte
}


void burbujeo (viaje & v, int i ) {
    for ( int j = v.size()-1; j > i ; j--) { // n^2 + cte
        if ( obtenerTiempo(v[ j ]) < obtenerTiempo(v[j -1])) { // n^2 + cte
            swap ( v, v[j] , v[j -1]) ; // n^2 + cte
        }
    }
}


viaje bubbleSort (viaje v) {
    for (int i=0; i<v.size(); i++) { // n + cte
        burbujeo(v, i) ; // n^2 + cte
    }
    return v;
}


double velocidad (tuple<tiempo,gps> ant, tuple<tiempo,gps> post){
    double difTiempo = (obtenerTiempo(post) - obtenerTiempo(ant)) / 3600;
    double dist = distEnKM(obtenerPosicion(ant), obtenerPosicion(post));
    double res = dist/difTiempo;
    return res;
}


tiempo encontrarMinimo(viaje v){
    tiempo min = obtenerTiempo(v[0]);
    for(int i = 0; i< v.size(); i++){
        if(obtenerTiempo(v[i]) < min){
            min = obtenerTiempo(v[i]);
        }
    }
    return min;
}

tiempo encontrarMaximo(viaje v){
    tiempo max = obtenerTiempo(v[0]);
    for(int i = 0; i< v.size(); i++){
        if(obtenerTiempo(v[i]) > max){
            max = obtenerTiempo(v[i]);
        }
    }
    return max;
}

bool medicionCubierta(gps coordenadas, viaje v, distancia u){
    bool res = false; // n + cte
    for(int i=0; i<v.size(); i++){ // n * m + cte
        if ((distEnKM((obtenerPosicion(v[i])),coordenadas)) <= u) { // n * m + cte
            res = true; // n * m + cte
        }
    }
    return res;
}

bool pertenece (celda c, grilla g){
    bool res = false;
    for (int i=0; i<g.size(); i++){
        if (c == g[i]){
            res = true;
        }
    }
    return res;
}


bool contenidoEn (grilla g, grilla gr){
    bool res = false;
    for (int i = 0; i < g.size(); i++){
        if (pertenece(g[i], gr)){
            res = true;
        }
    }
    return res;
}

gps obtenerEsqSup(tuple<gps, gps, nombre> esquina) {
    return get<0>(esquina);
}

gps obtenerEsqInf(tuple<gps, gps, nombre> esquina) {
    return get<1>(esquina);
}


double altoCelda(gps esq1, gps esq2, int n){
    return (obtenerLatitud(esq1)- obtenerLatitud(esq2)) / n;
}

double anchoCelda(gps esq1, gps esq2, int m){
    return (obtenerLongitud(esq2)- obtenerLongitud(esq1)) / m;
}


double latPosSupCelda(int nomb , gps esq1, gps esq2, int n) {
    double lat = obtenerLatitud(esq1) - altoCelda(esq1, esq2, n) * (nomb - 1);
    return lat;
}

double longPosSupCelda(int nomb , gps esq1, gps esq2, int m) {
    double lon = obtenerLongitud(esq1) + anchoCelda(esq1,esq2,m) * (nomb - 1);
    return lon;
}

double latPosInfCelda(double latPosSup, gps esq1, gps esq2, int n){
    double lat = latPosSup - altoCelda(esq1, esq2, n);
    return lat;
}

double longPosInfCelda(double longPosSup, gps esq1, gps esq2, int m){
    double lon = longPosSup + anchoCelda(esq1, esq2, m);
    return lon;
}

bool esCeldaDeCoordenada(gps p, celda c){
    bool res = false;
    if (get<0>(obtenerEsqInf(c)) < obtenerLatitud(p) && obtenerLatitud(p) <= get<0>(obtenerEsqSup(c))){
        if (get<1>(obtenerEsqSup(c)) <= obtenerLongitud(p) && obtenerLongitud(p) < get<1>(obtenerEsqInf(c))){
            res = true;
        }
    }
    return res;
}


celda asignarCelda(tuple<tiempo, gps> parada, grilla g) {
    celda res;
    for (int i = 0; i < g.size(); i++) {
        if (esCeldaDeCoordenada(get<1>(parada), g[i])) {
            res = g[i];
        }
    }
    return res;
}

double distanciaNombres(nombre actual, nombre siguiente){
    double dis1 = get<0>(actual) - get<0>(siguiente);
    double dis2 = get<1>(actual) - get<1>(siguiente);
    double dist = sqrt((pow(dis1,2) + pow(dis2,2)));
    return dist;
}




bool esError(tuple<tiempo,gps> p, error e){
    bool res = false;
    for (int i = 0; i<e.size(); i++){
        if (e[i] == get<0>(p)){
            res = true;
        }
    }
    return res;
}


void swapDeDiferencia (vector<tuple<tiempo,int>> &v, tuple<tiempo,int> &ant, tuple<tiempo,int> &post){
    tuple<tiempo,int> aux = ant;
    ant = post;
    post = aux;
}


void burbujeoDeDiferencia (vector<tuple<tiempo,int>> & v, int i ) {
    for ( int j = v.size()-1; j > i ; j--) {
        if ( get<0>(v[j]) < get<0>(v[j -1])){
            swapDeDiferencia( v, v[j], v[j -1]) ;
        }
    }
}


vector<tuple<tiempo,int>> bubbleSortDeDiferencia(vector<tuple<tiempo,int>> v) {
    for (int i=0; i<v.size(); i++) {
        burbujeoDeDiferencia(v, i) ;
    }
    return v;
}



vector<tuple<tiempo,int>> puntosValidosCercanos(int k, viaje v, error errores){
    vector<tuple<tiempo,int>> res;
    tiempo diferencia;
    for(int i = 0; i< v.size(); i++){
        if (not(esError(v[i], errores))){
            diferencia = abs(obtenerTiempo(v[k])- obtenerTiempo(v[i]));
            res.push_back(make_tuple(diferencia,i));
        }
    }
    vector<tuple<tiempo,int>> resultadoOrdenado = bubbleSortDeDiferencia(res);
    return resultadoOrdenado;
}




void swapInt(int &a, int &b){
    int aux = a;
    a = b;
    b = aux;
}


void cambio(gps &coord, viaje v, int k, error errores){
    vector<tuple<tiempo,int>> diferenciasDeErrores = puntosValidosCercanos(k, v, errores);

    int p = get<1>(diferenciasDeErrores[0]);
    int q = get<1>(diferenciasDeErrores[1]);

    if (p>q){
        swapInt(p,q);
    }
    double deltaLatPQ = (obtenerLatitud(obtenerPosicion(v[p])) - obtenerLatitud(obtenerPosicion(v[q])));
    double deltaLongPQ = (obtenerLongitud(obtenerPosicion(v[p])) - obtenerLongitud(obtenerPosicion(v[q])));
    double deltaTpoKP = ((obtenerTiempo(v[k]))-obtenerTiempo(v[p]));
    double deltaTpoPQ = (obtenerTiempo(v[p]) - obtenerTiempo(v[q]));

    get<0>(get<1>(v[k])) = deltaLatPQ * deltaTpoKP / deltaTpoPQ + obtenerLatitud(obtenerPosicion(v[p]));
    get<1>(get<1>(v[k])) = deltaLongPQ * deltaTpoKP / deltaTpoPQ + obtenerLongitud(obtenerPosicion(v[p]));

    coord = make_tuple(get<0>(get<1>(v[k])),(get<1>(get<1>(v[k]))));

}