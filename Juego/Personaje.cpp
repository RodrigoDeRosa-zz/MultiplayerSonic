#include "Personaje.hpp"
#include "../Graficos/Texture.hpp"
#include "../message.hpp"

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8
using namespace std;

Personaje::Personaje(string nomJugador){
    nombreJugador = nomJugador;
    bloque_pers = NULL;
    /*Cuando muere usa este bloque*/
    desaparecer = new MovingBloque(100, 425, 540, 120);
    desaparecer->setClip("move");
    desaparecer->setRectangulo("move", 0, 0, 108, 120);
    desaparecer->setRectangulo("move", 108, 0, 108, 120);
    desaparecer->setRectangulo("move", 216, 0, 108, 120);
    desaparecer->setRectangulo("move", 324, 0, 108, 120);
    desaparecer->setRectangulo("move", 432, 0, 108, 120);
    Texture* tex = new Texture();
    tex->loadFromFile("Graficos/desaparecer.png");
    desaparecer->setTexture(tex);
    /********************/
}

string Personaje::getNombreJugador(){
    return nombreJugador;
}

/*setters*/
void Personaje::setMovingBloque(MovingBloque* new_bloque){
    bloque_pers = new_bloque;
}

void Personaje::borrar(){
    bloque_pers->setAlfaCero();
}

/*Funciones de movimiento*/
void Personaje::update(float posX, float posY, move_type movimiento, int frame){

    bloque_pers->update(posX, posY);
    if(movimiento == IDLED){
        bloque_pers->quietoDerecha(frame);
    }
    else if (movimiento == DIE){
        setMovingBloque(desaparecer);
        bloque_pers->morir(frame);
    }
    else if(movimiento == IDLEI){
        bloque_pers->quietoIzquierda(frame);
    }
    else if(movimiento == JUMPI || movimiento == ROLLI){
        bloque_pers->jumpIzquierda(frame);
    }
    else if(movimiento == JUMPD || movimiento == ROLLD){
        bloque_pers->jumpDerecha(frame);
    }
    else if(movimiento == RUNI){
        bloque_pers->correrIzquierda(frame);
    }
    else if(movimiento == RUND){
        bloque_pers->correrDerecha(frame);
    }
    else if(movimiento == WALKI){
        bloque_pers->caminarIzquierda(frame);
    }
    else if(movimiento == WALKD){
        bloque_pers->caminarDerecha(frame);
    }
    else if(movimiento == WAITD){
        bloque_pers->esperandoDerecha(frame);
    }
    else if(movimiento == WAITI){
        bloque_pers->esperandoIzquierda(frame);
    }
    else if(movimiento == DMGD){
        bloque_pers->damageDerecha(frame);
    }
    else if(movimiento == DMGI){
        bloque_pers->damageIzquierda(frame);
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
