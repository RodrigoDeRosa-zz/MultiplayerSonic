#include "Entidad.hpp"

Entidad::Entidad(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

float Entidad::getX(){
	return this->x;
}

float Entidad::getY(){
	return this->y;
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

	return this->getY();
}

float Entidad::getBordeAbajo(){

	return this->getY() + (this->h);
}