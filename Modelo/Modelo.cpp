#include "Modelo.hpp"
#include <stdio.h>


Modelo::Modelo(gameMode mode){
    this->modoJuego = mode;

    /*Inicializaciones */
    players = new vector<Player*>();
    puntajes = new vector<Puntaje*>();
    vector<string>* nombresPuntajes	= new vector<string>();


    int cant_puntajes = 0;
    switch(this->modoJuego){
        case INDIVIDUAL:
            cant_puntajes = 4;
            nombresPuntajes->push_back(string("Jugador 1"));
            nombresPuntajes->push_back(string("Jugador 2"));
            nombresPuntajes->push_back(string("Jugador 3"));
            nombresPuntajes->push_back(string("Jugador 4"));
            break;
        case COOP:
            cant_puntajes = 1;
            nombresPuntajes->push_back(string("Jugadores"));
            break;
        case EQUIPOS:
            cant_puntajes = 2;
            nombresPuntajes->push_back(string("Equipo 1"));
            nombresPuntajes->push_back(string("Equipo 2"));
            break;
    }
    for (int i = 0; i < cant_puntajes; i++){
        Puntaje* p = new Puntaje(nombresPuntajes->at(i));
        puntajes->push_back(p);
    }

}

void Modelo::createPersonaje(string playerName, int equipo){//equipo puede ser 0 a 1
    Puntaje* p;
    switch(this->modoJuego){
        case INDIVIDUAL:
            p = puntajes->at(players->size() );break;
        case COOP:
            p = puntajes->front();break;
        case EQUIPOS:
            if (equipo==0){	//si es el primer o segundo jugador
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

gameMode Modelo::getGameMode(){
    return this->modoJuego;
}


vector<Player*>* Modelo::getPersonajes(){
    return this->players;
}

vector<Puntaje*>* Modelo::getPuntajes(){
    return this->puntajes;
}
