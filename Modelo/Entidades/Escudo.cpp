#include "Escudo.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 100
#define HEIGHT 120

using namespace std;

Escudo::Escudo(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Escudo::afectarA(Player* jugador){
	jugador->setEstado(ESCUDO);
	this->destruida = true;
}

out_message_t* Escudo::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(SHIELD_UPDATE);
	return state;
}

out_message_t* Escudo::getInitMessage(){
	return this->Entidad::getOutMessage(SHIELD_SET);
}

void Escudo::mover(){}
