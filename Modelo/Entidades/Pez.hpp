#ifndef PEZ_HPP
#define PEZ_HPP

#include "Entidad.hpp"

#define CONT_INICIAL 300 //para ajustar que despues se pase un poco

using namespace std;


class Pez: public Entidad{
	unsigned int contador_mov = CONT_INICIAL;
	float direccion = -1.0;
	float oldY;
public:
	Pez(int id, float x, float y);
	void afectarA(Player* jugador);
	out_message_t* getOutMessage();
	out_message_t* getInitMessage();
	void mover();
};

#endif /*PEZ_HPP*/
