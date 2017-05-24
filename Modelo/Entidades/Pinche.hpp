#ifndef PINCHE_HPP
#define PINCHE_HPP

#include "Entidad.hpp"

using namespace std;

class Pinche: public Entidad{
public:
	Pinche(float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
};

#endif /*PINCHE_HPP*/