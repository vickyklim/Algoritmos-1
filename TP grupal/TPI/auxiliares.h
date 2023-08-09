#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"


double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);


viaje bubbleSort (viaje v);


double velocidad (tuple<tiempo,gps> ant, tuple<tiempo,gps> post);

tiempo encontrarMinimo(viaje v);
tiempo encontrarMaximo(viaje v);

bool medicionCubierta(gps coordenadas, viaje v, distancia u);



bool contenidoEn (grilla g, grilla gr);

gps obtenerEsqSup(tuple<gps, gps, nombre> esquina);
gps obtenerEsqInf(tuple<gps, gps, nombre> esquina);


double latPosSupCelda(int nomb , gps esq1, gps esq2, int m);
double longPosSupCelda(int nomb , gps esq1, gps esq2, int n);

double latPosInfCelda(double latPosSup, gps esq1, gps esq2, int m);
double longPosInfCelda(double longPosSup, gps esq1, gps esq2, int n);

celda asignarCelda(tuple<tiempo, gps> parada, grilla g);
double distanciaNombres(nombre actual, nombre siguiente);

void cambio(gps &coord, viaje v, int i, error errores);

#endif //TRANSPORTEURBANO_AUXILIARES_H
