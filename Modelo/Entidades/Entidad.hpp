#ifndef ENTIDAD_HPP
#define ENTIDAD_HPP

#include "../Efecto.hpp"

class Entidad{
protected:
	float x;
	float y;
	float w;
	float h;
	Efecto* efecto;
public:
	Entidad(float x, float y);

	/*Getters*/
	float getX();
	float getY();
	float getCentroX();
	float getCentroY();
	float getBordeDer();
	float getBordeIzq();
	float getBordeArriba();
	float getBordeAbajo();
	Efecto* getEfecto();

	/*Setters*/
	void setEfecto(Efecto* efecto);
	void setW(float);
	void setH(float);
};
#endif /*ENTIDAD_HPP*/