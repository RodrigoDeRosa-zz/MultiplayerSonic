#ifndef TRANSICION_HPP
#define TRANSICION_HPP

#include "Nivel.hpp"


using namespace std;

class Transicion: public Nivel{
	public:
		Transicion();
		vector<string> getPlayerNames();
		void colisionarTodos();
		vector<out_message_t*> getStatus(float camPos);
		void moverEntidades();
};

#endif /*TRANSICION_HPP*/
