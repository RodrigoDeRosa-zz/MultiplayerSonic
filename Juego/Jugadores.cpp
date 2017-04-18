#include "Jugadores.hpp"
#include "Logger2.hpp"
#include "../Graficos/Camara.hpp"
using namespace std;

Jugadores::Jugadores(){}

void Jugadores::addJugador(string nombreJugador, string nombrePersonaje){
    Jugador* jug = new Jugador(nombreJugador, nombrePersonaje);
    //jugadores.insert(make_pair(nombreJugador,jug));
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

void Jugadores::render(Camara* camara){
      //for(std::map<string, Jugador*>::iterator it=jugadores.begin(); it!=jugadores.end(); ++it){
          //(jugadores[it->second]) -> render(camara);
      //}
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
