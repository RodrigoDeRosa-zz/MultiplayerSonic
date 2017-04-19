#include "Jugadores.hpp"
#include "Logger2.hpp"
#include "Personaje.hpp"
#include "Sonic.hpp"
#include "../Graficos/Camara.hpp"
using namespace std;

Jugadores::Jugadores(){}

bool Jugadores::addJugador(string nombreJugador, string nombrePersonaje){
    //aca en vez de crear un sonic hay que crear un personaje
    Jugador* jug = new Jugador(nombreJugador, nombrePersonaje);
    Sonic* newPersonaje = factory->getSonic(nombreJugador);
    if(newPersonaje){
      jug->setPersonaje(newPersonaje);
      jugadores[nombreJugador]=jug;
      return true;
    }
    return false;
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
