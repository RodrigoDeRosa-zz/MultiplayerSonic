#include "Personaje.hpp"
using namespace std;

Personaje::Personaje(string nomJugador){
    nombreJugador = nomJugador;
    bloque_pers = NULL;
}

string Personaje::getNombreJugador(){
    return nombreJugador;
}

void Personaje::setBloque(Bloque* new_bloque){
    bloque_pers = new_bloque;
}

bool Personaje::render(Camara* cam){
    if (!bloque_pers){
        bloque_pers->render(cam);
        return true;
    }
    //cambiar por llamada al logger
    printf("El bloque no pudo renderizarse");
    return false;
}

bool Personaje::operator==(Personaje& other) const{
    return (nombreJugador == other.getNombreJugador());
}
