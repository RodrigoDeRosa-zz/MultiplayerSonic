#include "Invencibilidad.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 100
#define HEIGHT 120

using namespace std;

Invencibilidad::Invencibilidad(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){
	frame = 1;
}

void Invencibilidad::afectarA(Player* jugador){
	jugador->setEstado(INVENCIBLE);
	this->destruida = true;
}

out_message_t* Invencibilidad::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(BONUS_UPDATE);
	return state;
}

out_message_t* Invencibilidad::getInitMessage(){
	return this->Entidad::getOutMessage(BONUS_SET);
}

void Invencibilidad::mover(){}
