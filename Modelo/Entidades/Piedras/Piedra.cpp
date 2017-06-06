#include "Piedra.hpp"
#include "../../Player.hpp"
#include <stdio.h>
#define WIDTH 124
#define HEIGHT 200
/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 5

using namespace std;

Piedra::Piedra(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Piedra::afectarA(Player* jugador){

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

out_message_t* Piedra::getOutMessage(){
	return this->Entidad::getOutMessage(ROCK_SET);
}

out_message_t* Piedra::getInitMessage(){
	return this->Entidad::getOutMessage(ROCK_SET);
}