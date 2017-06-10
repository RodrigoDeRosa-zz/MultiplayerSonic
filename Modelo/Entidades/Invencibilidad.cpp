#include "Invencibilidad.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 100
#define HEIGHT 120
#define FACTOR_DIFERENCIAL_H 5

using namespace std;

Invencibilidad::Invencibilidad(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){
	frame = 1;
}

void Invencibilidad::afectarA(Player* jugador){
	if(!(jugador->estaAtacando())){
			// el jugador no choca con el borde de arriba
		if(jugador->getBordeAbajo() > (this->Entidad::getBordeArriba() + FACTOR_DIFERENCIAL_H)){

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

		//seteo la y del jugador al borde superior de la piedra(teniendo en cuenta el alto de la imagen)
		else{
			float posicion = this->Entidad::getBordeArriba() -  /*el alto del frame actual*/ (jugador->getBordeAbajo() - jugador->getBordeArriba());
			//float posicion = jugador-> getBordeArriba() - ( this->Entidad::getBordeAbajo() - this->Entidad::getBordeArriba());
			jugador->caer();
			jugador->setY(posicion);
		}
	}
	else{
		jugador->setEstado(INVENCIBLE);
		this->destruida = true;
	}
}

out_message_t* Invencibilidad::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(BONUS_UPDATE);
	return state;
}

out_message_t* Invencibilidad::getInitMessage(){
	return this->Entidad::getOutMessage(BONUS_SET);
}

void Invencibilidad::mover(){}
