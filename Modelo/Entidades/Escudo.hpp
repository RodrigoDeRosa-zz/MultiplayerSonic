#ifndef ESCUDO_HPP
#define ESCUDO_HPP

#include "Entidad.hpp"

using namespace std;

class Escudo: public Entidad{
	unsigned int contador_mov = 0;
public:
	Escudo(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*ESCUDO_HPP*/