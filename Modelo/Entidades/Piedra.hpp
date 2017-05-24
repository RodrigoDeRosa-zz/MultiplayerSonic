#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "Entidad.hpp"

using namespace std;

class Piedra: public Entidad{
public:
	Piedra(float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
};

#endif /*PIEDRA_HPP*/