#include "Personaje.hpp"

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8
using namespace std;

int Personaje::getX(){
  return bloque_pers->getX();
}

int Personaje::getY(){
  return bloque_pers->getY();
}

Personaje::Personaje(string nomJugador){
    nombreJugador = nomJugador;
    bloque_pers = NULL;
    frameRight = 0;
    frameLeft = 0;
}

string Personaje::getNombreJugador(){
    return nombreJugador;
}

void Personaje::setMovingBloque(MovingBloque* new_bloque){
    bloque_pers = new_bloque;
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

void Personaje::update(float vel_x, float vel_y){
  if(vel_x> 0.0){
    moveRight(vel_x);}
  else if(vel_x < 0.0){
    moveLeft(vel_x);}
  else{
    //si no se movio para ningun lado ponemos las velocidades en 0
    bloque_pers->setVelocidades();
  }
}

void Personaje::moveRight(float vel_x){

    frameLeft = 0;
    if( frameRight / (FACTOR*WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
      frameRight=0;
    }

    bloque_pers->moveRight(frameRight, WALKING_ANIMATION_FRAMES, vel_x,FACTOR);
    frameRight++;
}

void Personaje::moveLeft(float vel_x){
    frameRight = 0;

    if( frameLeft / FACTOR*WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES){
      frameLeft=0;
    }

    bloque_pers->moveLeft(frameLeft, WALKING_ANIMATION_FRAMES, vel_x,FACTOR);
    frameLeft++;
}

bool Personaje::operator==(Personaje& other) const{
    return (nombreJugador == other.getNombreJugador());
}
