#ifndef BOLA_HPP
#define BOLA_HPP

#include "Entidad.hpp"
#include "Jefe.hpp"

using namespace std;

class Bola: public Entidad{
	int contador_mov = 0;
	bool direccion = true;//va para la derecha
	Jefe* jefe;
public:
	Bola(float x, float y, Jefe* j);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
	void destruir();
};

#endif /*BOLA_HPP*/
