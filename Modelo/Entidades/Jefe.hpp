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
	Jefe(float x, float y);//TODO: hace falta el id?
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
	void getAnclaje(float* x, float* y);//le pasa los valores desde donde calcular el MCU(V?)
};

#endif /*JEFE_HPP*/
