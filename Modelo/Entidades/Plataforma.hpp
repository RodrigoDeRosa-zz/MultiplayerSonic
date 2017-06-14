#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include "Entidad.hpp"

using namespace std;

class Plataforma: public Entidad{
public:
	Plataforma(int id,float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	bool esPiedra();
};

#endif /*PLATAFORMA_HPP*/