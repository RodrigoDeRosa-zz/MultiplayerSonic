#ifndef ENTIDAD_HPP
#define ENTIDAD_HPP

#include "../../message.hpp"

class Player;

class Entidad{
protected:
	int id;
	float x;
	float y;
	float w;
	float h;
	bool destruida;
	out_message_t* getOutMessage(message_type type);

public:
	Entidad(int id,float x, float y, float w, float h);

	virtual void afectarA(Player* jugador) = 0;
	virtual out_message_t* getOutMessage() = 0;
	virtual out_message_t* getInitMessage() = 0;
	virtual void mover();

	/*Getters*/
	int getId();
	float getX();
	float getY();
	float getCentroX();
	float getCentroY();
	float getBordeDer();
	float getBordeIzq();
	float getBordeArriba();
	float getBordeAbajo();
	bool estaDestruida();

	/*Setters*/
	void setW(float);
	void setH(float);
};
#endif /*ENTIDAD_HPP*/