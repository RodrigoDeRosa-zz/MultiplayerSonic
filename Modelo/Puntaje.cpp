#include "Puntaje.hpp"

Puntaje::Puntaje(string name){
	pthread_mutex_init(&puntaje_mux, NULL);
	contador=0;
	total=0;
	nombre = name;
}

/*
Puntaje::~Puntaje(){
}
*/

//Obtiene los puntos obtenidos en el nivel
long Puntaje::getParcial(){
	return contador;
}

//Obtiene los puntos que tiene en total
long Puntaje::getTotal(){
	return total;
}

//Pasa los puntos del nivel al total y resetea el contador por nivel
void Puntaje::pasarATotal(){
	pthread_mutex_lock(&puntaje_mux);
	total+=contador;
	contador=0;
	pthread_mutex_unlock(&puntaje_mux);
}

//Suma "p" puntos al contador por nivel
void Puntaje::sumarPuntos(int p){
	pthread_mutex_lock(&puntaje_mux);
	contador+=p;
	pthread_mutex_unlock(&puntaje_mux);
}

//getter del Nombre para facilitar impresión en pantalla de transición
string Puntaje::getNombre(){
	return nombre;
}
