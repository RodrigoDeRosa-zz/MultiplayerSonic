#include "Puntaje.hpp"


Puntaje::Puntaje(){
	pthread_mutex_init(&puntaje_mux, NULL);
	contador=0;
}
/*
Puntaje::~Puntaje(){
}
*/
long Puntaje::getPuntos(){
	return contador;
}

void Puntaje::sumarPuntos(int p){
	pthread_mutex_lock(&puntaje_mux);
	contador+=p;
	pthread_mutex_unlock(&puntaje_mux);
}
