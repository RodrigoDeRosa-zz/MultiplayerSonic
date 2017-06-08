#include "Transicion.hpp"
#include <stdio.h>

Transicion::Transicion(gameMode game_mode){

    this->modoJuego = game_mode;
}

void Transicion::setPuntajes( vector<Puntaje*>* vec ){
    this->puntajes = vec;
}