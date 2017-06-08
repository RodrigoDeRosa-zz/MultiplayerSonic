#ifndef TRANSICION_HPP
#define TRANSICION_HPP

#include <vector>
#include "../message.hpp"
#include "Puntaje.hpp"


using namespace std;

class Transicion{

    gameMode modoJuego;
    vector<Puntaje*>* puntajes;
	public:
		Transicion(gameMode);

        void setPuntajes( vector<Puntaje*>* );

};

#endif /*TRANSICION_HPP*/
