#ifndef PUNTAJE_HPP
#define PUNTAJE_HPP

#include <pthread.h>
#include <string>

using namespace std;

class Puntaje{
	private:
		pthread_mutex_t puntaje_mux;
		long contador;
		long total;
		string nombre;
	public:
		Puntaje(string name);
		string getNombre();
		long getParcial();
		long getTotal();
		void sumarPuntos(int p);
		void pasarATotal();
};

#endif //PUNTAJE_HPP
