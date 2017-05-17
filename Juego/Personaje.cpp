#include "Personaje.hpp"

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8
using namespace std;

Personaje::Personaje(string nomJugador){
nombreJugador = nomJugador;
bloque_pers = NULL;
}

string Personaje::getNombreJugador(){
    return nombreJugador;
}

/*setters*/
void Personaje::setMovingBloque(MovingBloque* new_bloque){
    bloque_pers = new_bloque;
}


/*Funciones de movimiento*/
void Personaje::update(float posX, float posY, move_type movimiento, int frame){

    if(movimiento == IDLED){
        bloque_pers->quietoDerecha(posX, posY, frame);
    }
    else if(movimiento == IDLEI){
        bloque_pers->quietoIzquierda(posX, posY, frame);
    }
    else if(movimiento == JUMPD){
        bloque_pers->jumpIzquierda(posX, posY, frame);
    }
    else if(movimiento == JUMPI){
        bloque_pers->jumpDerecha(posX, posY, frame);
    }
    else if(movimiento == RUND){
        bloque_pers->correrIzquierda(posX, posY, frame);
    }
    else if(movimiento == RUNI){
        bloque_pers->correrDerecha(posX, posY, frame);
    }
    else if(movimiento == WALKD){
        bloque_pers->caminarIzquierda(posX, posY, frame);
    }
    else if(movimiento == WALKI){
        bloque_pers->caminarDerecha(posX, posY, frame);
    }
}

void Personaje::grisearBolque(){
    bloque_pers->grisearTexture();
}

void Personaje::desGrisearBolque(){
    bloque_pers->desGrisearTexture();
}

bool Personaje::operator==(Personaje& other) const{
    return (nombreJugador == other.getNombreJugador());
}

float Personaje::getX(){
    return bloque_pers->getX();
}

float Personaje::getY(){
    return bloque_pers->getY();
}

bool Personaje::render(Camara* cam){
    if(bloque_pers){
        //esta linea es la que falla
        bloque_pers->render(cam);
        return true;
    }
    //cambiar por llamada al logger
    printf("El bloque no pudo renderizarse\n");
    return false;
}
