#ifndef CANGREJO_HPP
#define CANGREJO_HPP

#include "Entidad.hpp"

using namespace std;

class Cangrejo: public Entidad{
	unsigned int contador_mov = 0;
	float direccion = 1.0;
public:
	Cangrejo(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*CANGREJO_HPP*/
