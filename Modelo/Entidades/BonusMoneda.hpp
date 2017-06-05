#ifndef MONEDABONUS_HPP
#define MONEDABONUS_HPP

#include "Entidad.hpp"

using namespace std;

class BonusMoneda: public Entidad{
	unsigned int contador_mov = 0;
public:
	BonusMoneda(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*MONEDABONUS_HPP*/