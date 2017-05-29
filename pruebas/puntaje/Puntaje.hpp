#ifndef PUNTAJE_HPP
#define PUNTAJE_HPP

#include "pthread.h"

class Puntaje{
	private:
		pthread_mutex_t puntaje_mux;
		unsigned long contador;
	public:
		unsigned long getPuntos();
		void sumarPuntos(int p);
}

#endif //PUNTAJE_HPP
