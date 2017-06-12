#ifndef TRANSICION_HPP
#define TRANSICION_HPP

#include "Nivel.hpp"


using namespace std;

class Transicion: public Nivel{
	int update_counter;
	pthread_t timeThreadID;
	public:
		Transicion();
		vector<string> getPlayerNames();
		void colisionarTodos();
		vector<out_message_t*> getStatus(float camPos);
		void moverEntidades();
		void setTermino();
		void terminar();
		void start();
};

#endif /*TRANSICION_HPP*/
