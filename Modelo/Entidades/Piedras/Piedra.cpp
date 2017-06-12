#include "Piedra.hpp"
#include "../../Player.hpp"
#include <stdio.h>
#define WIDTH 124
#define HEIGHT 200
/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 5
#define THRESHOLD_DIST	10.0

using namespace std;

Piedra::Piedra(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){
	this->setPiedra();
}

void Piedra::afectarA(Player* jugador){

	// el jugador no choca con el borde de arriba
	if(jugador->getBordeAbajo() > (this->Entidad::getBordeArriba() + FACTOR_DIFERENCIAL_H)){

		float posicion = jugador->getX();
		// el jugador venia de la izquierda y se choca con el costado izquierdo de la piedra
		if(jugador->getDirX() > 0){
		//TODO: reemplazar por un getter de direccion del moveSonic
			posicion = this->Entidad::getBordeIzq() - (jugador->getBordeDer() - jugador->getBordeIzq()) - 5;
		}
		// el jugador venia de la derecha sin saltar y se choca con el costado derecho de la piedra
		else if(jugador->getDirX() < 0 ){
		//TODO: reemplazar por un getter de direccion del moveSonic
			posicion = this->Entidad::getBordeDer() + 5;
		}
		jugador->setX(posicion);
	}

	//seteo la y del jugador al borde superior de la piedra(teniendo en cuenta el alto de la imagen)
	else{
		float posicion = this->Entidad::getBordeArriba() -  (jugador->getBordeAbajo() - jugador->getBordeArriba()); /*el alto del frame actual*/
		//float posicion = jugador-> getBordeArriba() - ( this->Entidad::getBordeAbajo() - this->Entidad::getBordeArriba());
	
		//TODO: agregar un getter de direccion del moveSonic, asi si viene de la izquierda y toca borde izquierdo no colisiona
		if (jugador->getX() > (this->Entidad::getBordeDer() - THRESHOLD_DIST)){
			jugador->caer(1);
			jugador->setY(posicion);
			return;
		}
		if (jugador->getX() < (this->Entidad::getBordeIzq() + THRESHOLD_DIST)){
			jugador->caer(-1);
			jugador->setY(posicion);
			return;		
		}
		//esta en el medio
		jugador->setY(posicion);
	
		
		/*
		jugador->caer(0);
		jugador->setY(posicion);
		*/
	}
}

out_message_t* Piedra::getOutMessage(){
	return this->Entidad::getOutMessage(ROCK_SET);
}

out_message_t* Piedra::getInitMessage(){
	return this->Entidad::getOutMessage(ROCK_SET);
}
