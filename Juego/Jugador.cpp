#include "Jugador.hpp"

Jugador::Jugador(string nomJugador, string nomPersonaje, Texture* bolas){
    nombreJugador = nomJugador;
    nombrePersonaje = nomPersonaje;
    personaje = NULL;
    efectoActual = NORMAL;

    escudo = new Escudo(0, 0);
    escudo->setTexture(bolas);
    escudo->setIndexZ(100);

    invencibilidad = new Invencibilidad(0, 0);
    invencibilidad->setTexture(bolas);
    invencibilidad->setIndexZ(100);
}

void Jugador::updatePersonaje(float posx, float posy, move_type movimiento, int frame, bool conectado,
    state_type state, int state_frame){
    if(personaje == NULL){
    //LOGGER
    }
    if(conectado == false){
      //si esta desconectado entonces se lo grisa y se actualiza la posicion dejandolo quieto
      personaje->grisearBolque();
    } else{
      personaje->desGrisearBolque();
    }

    if (state != NORMAL){
        if (state == INVENCIBLE){
            efectoActual = INVENCIBLE;
            //print("frame: %d \n", state_frame);
            invencibilidad->setFrame(state_frame);
            invencibilidad->update(posx-10, posy-10);
        } else {
            efectoActual = ESCUDO;
            escudo->setFrame(state_frame);
            escudo->update(posx-10, posy);
        }
    } else efectoActual = NORMAL;

    personaje->update(posx, posy, movimiento, frame);

}

void Jugador::setPersonaje(Personaje* new_personaje){
    personaje = new_personaje;
}

void Jugador::render(Camara* cam){
    personaje->render(cam);
    if (efectoActual == INVENCIBLE) invencibilidad->render(cam);
    else if (efectoActual == ESCUDO) escudo->render(cam);
}
string Jugador::getNombre(){
    return nombreJugador;
}

bool Jugador::operator==(Jugador& other) const{
    return (nombreJugador == other.getNombre());
}

Jugador::~Jugador(){
    if (escudo){
        delete escudo;
        escudo = NULL;
    }
    if (invencibilidad){
        delete invencibilidad;
        invencibilidad = NULL;
    }
}
