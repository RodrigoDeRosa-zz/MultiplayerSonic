#include "Estado.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

Estado::Estado(){
	this->estado = NORMAL;
	this->frame = 0;
	this->frameSum = 0;
}

state_type Estado::get(){
	return this->estado;
}

void Estado::set(state_type estado){
	if(this->estado == PRUEBA){
		if(estado == NORMAL) this->estado = estado;
	}
	else{
		if(estado == INVENCIBLE) this->setInvencible();
		else if(estado == REVIVIENDO) this->setReviviendo();
		else this->estado = estado;
	}
}

void* invencibility(void* arg){
	Estado* estado = (Estado*)arg;
	sleep(10);
	if(estado->get() == INVENCIBLE) estado->set(NORMAL);
	return NULL;
}

void* respawn(void* arg){
	Estado* estado = (Estado*)arg;
	sleep(2);
	if(estado->get() == REVIVIENDO) estado->set(NORMAL);
	return NULL;
}

void Estado::setInvencible(){
	this->estado = INVENCIBLE;
	pthread_t timeThreadID;
	pthread_create(&timeThreadID, NULL, invencibility, this);
}

void Estado::setReviviendo(){
	this->estado = REVIVIENDO;
	pthread_t timeThreadID;
	pthread_create(&timeThreadID, NULL, respawn, this);
}

void Estado::updateFrame(){
	frameSum++;
	if (frameSum > 100) frameSum = 0;
	if (frameSum%10 == 0){
		frame = frameSum / 10;
	}
	if(frame >= 9) frame = 0;
}

int Estado::getFrame(){
	this->updateFrame();
	return this->frame;
}

bool Estado::recibirGolpe(){
	switch(this->estado){
		case INVENCIBLE:
			return false;
		case ESCUDO:
			this->set(NORMAL);
			return false;
		case NORMAL:
			return true;
		case PRUEBA:
			return false;
		case REVIVIENDO:
			return false;
	}
}
