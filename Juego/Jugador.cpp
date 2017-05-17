#include "Jugador.hpp"

Jugador::Jugador(string nomJugador, string nomPersonaje){
    nombreJugador = nomJugador;
    nombrePersonaje = nomPersonaje;
    personaje = NULL;
}

float,float,move_type,int,bool
void Jugador::updatePersonaje(float posx, float posy, move_type movimiento, int frame, bool conectado){
    if(personaje == NULL){
    //LOGGER
    }
    if(conectado == false){
      //si esta desconectado entonces se lo grisa y se actualiza la posicion dejandolo quieto
      personaje->grisearBolque();
    }
    else{
      personaje->desGrisearBolque();
    }
    personaje->update(posx, posy, movimiento, frame);

}

void Jugador::setPersonaje(Personaje* new_personaje){
    personaje = new_personaje;
}

void Jugador::render(Camara* cam){
    personaje->render(cam);
}
string Jugador::getNombre(){
    return nombreJugador;
}

bool Jugador::operator==(Jugador& other) const{
    return (nombreJugador == other.getNombre());
}

Jugador::~Jugador(){}
