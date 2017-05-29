#ifndef BOLA_HPP
#define BOLA_HPP

#include "Entidad.hpp"
#include "Jefe.hpp"

using namespace std;

class Bola: public Entidad{
	int contador_mov = 0;
	bool direccion = true;//va para la derecha
	Jefe* jefe;	//TODO: acomodar constructor para que reciba esto!
public:
	Bola(int id, float x, float y); //TODO: hace falta el id?
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*BOLA_HPP*/
