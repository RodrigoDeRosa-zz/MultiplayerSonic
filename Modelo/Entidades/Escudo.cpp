#include "Escudo.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 100
#define HEIGHT 120

using namespace std;

Escudo::Escudo(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){
	frame = 2;
}

void Escudo::afectarA(Player* jugador){
	if(!(jugador->estaAtacando())){
			// el jugador no choca con el borde de arriba

		float posicion = jugador->getX();
		// el jugador venia de la izquierda y se choca con el costado izquierdo de la piedra
		if(jugador->getDirX() > 0){
			posicion = this->Entidad::getBordeIzq() - (jugador->getBordeDer() - jugador->getBordeIzq()) - 5;
		}
		// el jugador venia de la derecha sin saltar y se choca con el costado derecho de la piedra
		else if(jugador->getDirX() < 0 ){
			posicion = this->Entidad::getBordeDer() + 5;
		}
		jugador->setX(posicion);
	}
	else{
		jugador->setEstado(ESCUDO);
		this->destruida = true;
	}
}

out_message_t* Escudo::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(BONUS_UPDATE);
	return state;
}

out_message_t* Escudo::getInitMessage(){
	return this->Entidad::getOutMessage(BONUS_SET);
}

void Escudo::mover(){}
