#include "Jugadores.hpp"
#include "Logger2.hpp"
using namespace std;

Jugadores::Jugadores(){}

void Jugadores::add(Jugador* jugador){
    jugadores[jugador->getNombre()] = jugador;
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
