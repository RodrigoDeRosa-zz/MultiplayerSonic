#ifndef PINCHE_HPP
#define PINCHE_HPP

#include "Entidad.hpp"

using namespace std;

class Pinche: public Entidad{
public:
	Pinche(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
};

#endif /*PINCHE_HPP*/