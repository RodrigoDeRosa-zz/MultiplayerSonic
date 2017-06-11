#include "Transicion.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* end_transition(void* arg){
	Transicion* trancision = (Transicion*)arg;
	sleep(10);
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
	//mando 5 veces el mensaje de jugadores por las dudas de que una vez no llegue, despues solo frame updates
	if(this->update_counter < 5){
		for(int i=0; i < (this->players)->size(); i++){
			v.push_back((*(this->players))[i]->getStatus(camPos));
		}
		this->update_counter++;
	}

	//mensaje de actualizar frame
	out_message_t* state = new out_message_t;
	memset(state, 0, sizeof(out_message_t));
	state->ping = TRANSITION_UPDATE;
	state->id = 0;
	state->connection = true;
	state->posX = 0;
	state->posY = 0;
	state->camPos = 0;
	state->move = MOVE_TOTAL;
	state->frame = this->frame;
	state->rings = 0;
	state->lives = 0;
	state->points = 0;
	state->state = NORMAL;
	state->state_frame = 0;
	v.push_back(state);
	//

	this->frame++;
	return v;
}
