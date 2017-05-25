#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "Entidad.hpp"

using namespace std;

class Moneda: public Entidad{
public:
	Moneda(float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
};

#endif /*MONEDA_HPP*/