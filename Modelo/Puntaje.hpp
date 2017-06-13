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
		int monedas;
		string nombre;
	public:
		Puntaje(string name);
		string getNombre();
		long getParcial();
		long getTotal();
		void sumarPuntos(int p);
		void pasarATotal();
		int getMonedas();
		void sumarMonedas(int m);
};

#endif //PUNTAJE_HPP
