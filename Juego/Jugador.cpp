#include "Jugador.hpp"

Jugador::Jugador(string nomJugador, string nomPersonaje){
    nombreJugador = nomJugador;
    nombrePersonaje = nomPersonaje;
    personaje = NULL;
}

void Jugador::updatePersonaje(float velx, float vely, float posx, float posy, float conectado){
  if(personaje == NULL){
    //LOGGER
  }
  if(conectado == false){
      personaje->grisearBolque();
  }
  else{
      personaje->desGrisearBolque();
  }
  personaje->update(velx, vely);
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
