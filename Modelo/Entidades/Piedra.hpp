#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "Entidad.hpp"

using namespace std;

class Piedra: public Entidad{
public:
	Piedra(float x, float y, float w, float h);
	void afectarA(Player* jugador);
};

#endif /*PIEDRA_HPP*/