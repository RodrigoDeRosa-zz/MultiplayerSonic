#include "Entidad.hpp"

Entidad::Entidad(float x, float y){
	this->x = x;
	this->y = y;
}

float Entidad::getX(){
	return this->x;
}

float Entidad::getY(){
	return this->y;
}

Efecto* Entidad::getEfecto(){
	return this->efecto;
}

void Entidad::setEfecto(Efecto* efecto){
	this->efecto = efecto;
}