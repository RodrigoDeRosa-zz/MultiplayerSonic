#ifndef MOSCA_HPP
#define MOSCA_HPP

#include "Entidad.hpp"

using namespace std;

class Mosca: public Entidad{
public:
	Mosca(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*MOSCA_HPP*/