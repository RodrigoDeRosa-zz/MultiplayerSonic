#include "Piedra.hpp"
#include "../../Player.hpp"
#include <stdio.h>
#define WIDTH 124
#define HEIGHT 200
/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 5
#define THRESHOLD_DIST	45.0
#define THRESHOLD_MIN	15.0
#define THRESHOLD_NO_COL 5.0

using namespace std;


Piedra::Piedra(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

bool Piedra::esPiedra(){
	return true;
}

void Piedra::afectarA(Player* jugador){
/*
	if(jugador->getBordeDer() > (this->Entidad::getBordeDer() - THRESHOLD_NO_COL)){
		jugador->setBaseY(425);
		return;
	}
*/
	// el jugador no choca con el borde de arriba
	if(jugador->getBordeAbajo() > (this->Entidad::getBordeArriba() + FACTOR_DIFERENCIAL_H)){

		float posicion = jugador->getX();

		//MIRANDO SOLO LA DIRECCION
/*
		
		// el jugador venia de la izquierda y se choca con el costado izquierdo de la piedra
		if(jugador->getDirX() > 0){
			posicion = this->Entidad::getBordeIzq() - (jugador->getBordeDer() - jugador->getBordeIzq()) - 5;
		}
		// el jugador venia de la derecha sin saltar y se choca con el costado derecho de la piedra
		else if(jugador->getDirX() < 0 ){
			posicion = this->Entidad::getBordeDer() + 5;
		}
		jugador->setX(posicion);
		
		//SOLO DIRECCION
*/

		//MIRANDO SOLO LA POSICION
		
		//si ademas esta cayendo hacia algun lado, entonces que no toque la X


		//caso especial caida
		if(posicion < (this->Entidad::getBordeIzq()+WIDTH/2.0)){//esta en la mitad izquierda de la piedra
			posicion = this->Entidad::getBordeIzq() - (jugador->getBordeDer() - jugador->getBordeIzq()) - FACTOR_DIFERENCIAL_H;		
		}
		else{//esta en la mitad derecha de la piedra
			posicion = this->Entidad::getBordeDer() + FACTOR_DIFERENCIAL_H;
		}
		jugador->setX(posicion);

		//SOLO POSICION
	}

	//seteo la y del jugador al borde superior de la piedra(teniendo en cuenta el alto de la imagen)
	else{
		float posicion = this->Entidad::getBordeArriba() -  (jugador->getBordeAbajo() - jugador->getBordeArriba()); /*el alto del frame actual*/
		//float posicion = jugador-> getBordeArriba() - ( this->Entidad::getBordeAbajo() - this->Entidad::getBordeArriba());

		if (jugador->getX() > (this->Entidad::getBordeDer() - THRESHOLD_DIST) && jugador->estaMirandoADer()){
			jugador->caer(1);
			jugador->setBaseY(425);
			if (jugador->getX() > (this->Entidad::getBordeDer() - THRESHOLD_MIN)){
				//jugador->setY(posicion);
			}
			return;
		}
		if (jugador->getBordeDer() < (this->Entidad::getBordeIzq() + THRESHOLD_DIST) && !(jugador->estaMirandoADer())){
			jugador->caer(-1);
			jugador->setBaseY(425);
			if (jugador->getBordeDer() < (this->Entidad::getBordeIzq() + THRESHOLD_MIN)){
				//jugador->setY(posicion);
			}
			return;
		}

		//esta en el medio
		if (jugador->getY() > posicion){
			jugador->setY(posicion);
		}
		jugador->setBaseY(posicion);


		/*
		jugador->caer(0);
		jugador->setY(posicion);
		*/
	}
}

out_message_t* Piedra::getOutMessage(){
	return this->Entidad::getOutMessage(MESSAGE_TOTAL);
}

out_message_t* Piedra::getInitMessage(){
	return this->Entidad::getOutMessage(ROCK_SET);
}
