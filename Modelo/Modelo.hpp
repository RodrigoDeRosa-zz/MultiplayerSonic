#ifndef MODELO_HPP
#define MODELO_HPP

#include <vector>
#include "Player.hpp"

using namespace std;

class Modelo {
	/*El nuevo modelo contiene las cosas que son generales para todos
	 * los niveles. Los jugadores y los puntajes. Se inicializan y se
	 * quedan guardados aca, para que cada vez que se necesite instanciar
	 * un nuevo nivel, el modelo pueda brindarle lo que necesita*/

	vector<Player *> *players;
	vector<Puntaje *> *puntajes;
	gameMode modoJuego;

	public:
		Modelo(gameMode);
		void createPersonaje(string playerName, int equipo);

		gameMode getGameMode();

		vector<Player*>* getPersonajes();
		vector<Puntaje*>* getPuntajes();
};

#endif /*MODELO_HPP*/
