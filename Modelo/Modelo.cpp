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

Player* Modelo::getPlayer(string nombre){
	for(int i = 0; i < players->size(); i++){
		if(((*players)[i])->getName() == nombre){
			return (*players)[i];
		}
	}
	return NULL;
}

void Modelo::createPersonaje(string playerName, int equipo){//equipo puede ser 1 o 2
    Puntaje* p;
    switch(this->modoJuego){
        case INDIVIDUAL:
            p = puntajes->at(players->size() );break;
        case COOP:
            p = puntajes->front();break;
        case EQUIPOS:
            if (equipo==1){	//equipo 1
                p = puntajes->front();
            }
            else{						//equipo 2
                p = puntajes->back();
            }
            break;
    }
    Player* player = new Player(playerName, p);
    (this->players)->push_back(player);

}

void Modelo::cambiarEquipo(string playerName, int equipo){//TODO REVISAR QUE ANDE
	Player* player;
	Puntaje* p;

	player = this->getPlayer(playerName);
	if (equipo==1){	//equipo 1
		p = puntajes->front();
	}
	else{			//equipo 2
		p = puntajes->back();
	}
	player->cambiarEquipo(p);
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
