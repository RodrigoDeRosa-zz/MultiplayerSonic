#ifndef PUNTAJE_HPP
#define PUNTAJE_HPP

#include <pthread.h>

class Puntaje{
	private:
		pthread_mutex_t puntaje_mux;
		long contador;
	public:
		Puntaje();
		long getPuntos();
		void sumarPuntos(int p);
};

#endif //PUNTAJE_HPP
