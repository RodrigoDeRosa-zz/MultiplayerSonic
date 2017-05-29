#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "Entidad.hpp"

using namespace std;

class Moneda: public Entidad{
	unsigned int contador_mov = 0;
public:
	Moneda(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*MONEDA_HPP*/
