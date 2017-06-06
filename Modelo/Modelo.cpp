#include "Modelo.hpp"
#include <stdio.h>

Modelo::Modelo(gameMode mode){
    this->modoJuego = mode;
}

void Modelo::createPersonaje(string playerName){
    Puntaje* p;
    switch(this->modoJuego){
        case INDIVIDUAL:
            p = puntajes->at(players->size());break;
        case COOP:
            p = puntajes->front();break;
        case EQUIPOS:
            if (players->size() < 2){	//si es el primer o segundo jugador
                p = puntajes->front();
            }
            else{						//sino es el tercer o cuarto
                p = puntajes->back();
            }
            break;
    }
    Player* player = new Player(playerName, p);
    //TODO CAMBIAR CONSTRUCTOR DE PLAYER PARA QUE RECIBA PUNTAJE
    (this->players)->push_back(player);
}


vector<Player*>* Modelo::getPersonajes(){
    return this->players;
}