#include "Jugadores.hpp"
#include "Logger2.hpp"
#include "Personaje.hpp"
#include "Sonic.hpp"
#include "../Graficos/Camara.hpp"
using namespace std;

#define SONIC1 "SONIC"
#define SONIC2 "Sonic"
#define SONIC3 "sonic"

Jugadores::Jugadores(){}

bool Jugadores::addSonic(string nombreJugador, string nombrePersonaje, Jugador* jug){
  //funcion que devuelve a sonic
    Sonic* newPersonaje = factory->getSonic(nombreJugador);
    if(newPersonaje){
      jug->setPersonaje(newPersonaje);
      jugadores[nombreJugador]=jug;
      return true;
    }
    return false;

}

bool Jugadores::addJugador(string nombreJugador, string nombrePersonaje){

    Jugador* jug = new Jugador(nombreJugador, nombrePersonaje);
    bool exito = false;
    //como c++ no deja hacer switch con strings hacemos ifs.
    if( (nombrePersonaje == SONIC1) || (nombrePersonaje == SONIC2) || (nombrePersonaje == SONIC3)){
      exito = addSonic(nombreJugador, nombrePersonaje, jug);
    }
    return exito;
}

bool Jugadores::remove(string nombreJugador){
    //falta chequear si es el jugador actual
    std::map<string, Jugador*>::iterator elem = jugadores.find(nombreJugador);
    if (elem != jugadores.end()){
        jugadores.erase(nombreJugador);
        return true;
    }
    return false;
}

void Jugadores::setFactory(SegaFactory* fact){
    factory=fact;
}

void Jugadores::render(Camara* camara){
      for(std::map<string, Jugador*>::iterator it=jugadores.begin(); it!=jugadores.end(); it++){
          string clave = it->first;
          Jugador* actual = jugadores[clave];
          actual->render(camara);
      }
}

void Jugadores::update(){
    //update
}

void Jugadores::empty() {
	jugadores.clear();
}

bool Jugadores::has(string nombreJugador) {
  std::map<string, Jugador*>::iterator elem = jugadores.find(nombreJugador);
  if (elem != jugadores.end()){
      return true;
  }
  return false;
}

Jugadores::~Jugadores(){}
