#include "Jugador.hpp"

Jugador::Jugador(string nomJugador, string nomPersonaje){
    cam = NULL;
    nombreJugador = nomJugador;
    nombrePersonaje = nomPersonaje;
}

string Jugador::getNombre(){
    return nombreJugador;
}

void Jugador::setCamara(Camara* new_cam){
    cam = new_cam;
    //falta crear un personaje y asignarselo a la camara
}

bool Jugador::operator==(Jugador& other) const{
    return (nombreJugador == other.getNombre());
}

Jugador::~Jugador(){}
