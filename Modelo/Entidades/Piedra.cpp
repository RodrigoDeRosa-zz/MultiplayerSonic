#include "Piedra.hpp"
#include "../Player.hpp"

/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 10

using namespace std;

Piedra::Piedra(float x, float y, float w, float h) : Entidad(x,y,w,h){}

void Piedra::afectarA(Player* jugador){

	// el jugador no choca con el borde de arriba
	if(jugador->getBordeAbajo() > (this->Entidad::getBordeArriba() + FACTOR_DIFERENCIAL_H)){
		float posicion;
		// el jugador venia de la izquierda y se choca con el costado izquierdo de la piedra
		if(jugador->getDirX() > 0) posicion = this->Entidad::getBordeIzq() - jugador->getBordeDer();
		// el jugador venia de la derecha sin saltar y se choca con el costado derecho de la piedra
		else if(jugador->getDirX() < 0 ) posicion = this->Entidad::getBordeDer() + /*ancho del jugador*/(jugador->getX() - jugador->getBordeIzq());
		jugador->setX(posicion);
	}

	//seteo la y del jugador al borde superior de la piedra(teniendo en cuenta el alto de la imagen)
	else{
		jugador->setY(this->getBordeArriba() - /* el alto del frame actual */(jugador->getBordeAbajo() - jugador->getBordeArriba()));
	}
}