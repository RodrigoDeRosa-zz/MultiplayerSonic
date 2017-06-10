#include "Transicion.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* end_transition(void* arg){
	Transicion* trancision = (Transicion*)arg;
	sleep(30);
	trancision->terminar();
	return NULL;
}

Transicion::Transicion(): Nivel(){
	pthread_t timeThreadID;
	void* timeThread_exit;
	pthread_create(&timeThreadID, NULL, end_transition, this);
}

vector<string> Transicion::getPlayerNames(){
	vector<string> v;
	return v;
}

void Transicion::colisionarTodos(){}

void Transicion::moverEntidades(){}

vector<out_message_t*> Transicion::getStatus(float camPos){
	vector<out_message_t*> v;
	for(int i=0; i < (this->players)->size(); i++){
		v.push_back((*(this->players))[i]->getStatus(camPos));
	}
	// hacer algo con los frames
	return v;
}
