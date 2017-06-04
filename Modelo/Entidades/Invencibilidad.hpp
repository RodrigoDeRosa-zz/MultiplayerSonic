#ifndef INVENCIBILIDAD_HPP
#define INVENCIBILIDAD_HPP

#include "Entidad.hpp"

using namespace std;

class Invencibilidad: public Entidad{
	unsigned int contador_mov = 0;
public:
	Invencibilidad(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*INVENCIBILIDAD_HPP*/