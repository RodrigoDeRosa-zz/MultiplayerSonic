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

void Entidad::setW(float x){
	this->w = w;
}

void Entidad::setH(float x){
	this->h = w;
}

float Entidad::getCentroX(){

	return this->getX() + (this->w / 2);
}

float Entidad::getCentroY(){

	return this->getY() + (this->h / 2);
}

float Entidad::getBordeDer(){

	return this->getX() + (this->w);
}

float Entidad::getBordeIzq(){

	return this->getX();
}

float Entidad::getBordeArriba(){

	return this->getY() + (this->h);
}

float Entidad::getBordeAbajo(){

	return this->getY();
}