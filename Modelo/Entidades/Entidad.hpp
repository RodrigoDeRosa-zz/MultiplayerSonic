#ifndef ENTIDAD_HPP
#define ENTIDAD_HPP

class Player;

class Entidad{
protected:
	float x;
	float y;
	float w;
	float h;
public:
	Entidad(float x, float y, float w, float h);

	virtual void afectarA(Player* jugador) = 0;

	/*Getters*/
	float getX();
	float getY();
	float getCentroX();
	float getCentroY();
	float getBordeDer();
	float getBordeIzq();
	float getBordeArriba();
	float getBordeAbajo();

	/*Setters*/
	void setW(float);
	void setH(float);
};
#endif /*ENTIDAD_HPP*/