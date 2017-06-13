#ifndef JEFE_HPP
#define JEFE_HPP

#include "Entidad.hpp"

#define CANT_VIDAS_JEFE 3


using namespace std;

class Jefe: public Entidad{
	unsigned int contador_mov = 0;
	float direccion = 1.0;
	int vidas = CANT_VIDAS_JEFE;
	void recibirDanio();
public:
	Jefe(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
	void getAnclaje(float* targetX, float* targetY);
};

#endif /*JEFE_HPP*/
