#include "Jugador.hpp"

Jugador::Jugador(string nomJugador, string nomPersonaje){
    nombreJugador = nomJugador;
    nombrePersonaje = nomPersonaje;
}

void Jugador::render(Camara* cam){
    //personaje->render(cam);
}
string Jugador::getNombre(){
    return nombreJugador;
}

bool Jugador::operator==(Jugador& other) const{
    return (nombreJugador == other.getNombre());
}

Jugador::~Jugador(){}
