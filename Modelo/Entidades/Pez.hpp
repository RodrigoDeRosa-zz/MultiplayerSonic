#ifndef PEZ_HPP
#define PEZ_HPP

#include "Entidad.hpp"

using namespace std;

class Pez: public Entidad{
public:
	Pez(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*PEZ_HPP*/