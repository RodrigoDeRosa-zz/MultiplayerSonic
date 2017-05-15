#include "Personaje.hpp"

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8
using namespace std;

Personaje::Personaje(string nomJugador){
  nombreJugador = nomJugador;
  bloque_pers = NULL;
  frameRight = 0;
  frameLeft = 0;
  direccionX = 0.0;
  direccionY = 0.0;
}

string Personaje::getNombreJugador(){
    return nombreJugador;
}

void Personaje::printMap(){
  bloque_pers->printMap();
}

/*setters*/
void Personaje::setMovingBloque(MovingBloque* new_bloque){
    bloque_pers = new_bloque;
}


/*Funciones de movimiento*/
void Personaje::update(float vel_x, float vel_y, float posX, float posY){
  //si no se pasa una posicion al update, este no la modifica
  if(posX >= 0 || posX >= 0){
      bloque_pers->update(posX, posY);
  }

  if(vel_y< 0.0 || bloque_pers->estaSaltando()){
     jump(vel_x,vel_y);
  }
  else if(vel_x> 0.0){
    moveRight(vel_x);}
  else if(vel_x < 0.0){
    moveLeft(vel_x);}

  //si no se movio para ningun seteamos las velocidades y frames a 0
  else{
    bloque_pers->setPosicionInicio();
  }
    direccionX = vel_x;
    direccionY = vel_y;
}

void Personaje::moveRight(float vel_x){
    bloque_pers->moveRight(vel_x);
}

void Personaje::moveLeft(float vel_x){
    bloque_pers->moveLeft(vel_x);
}

void Personaje::jump(float vel_x, float vel_y){
  bloque_pers->jump(vel_x,vel_y);
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

float Personaje::getDirX(){
    return direccionX;
}

float Personaje::getDirY(){
    return direccionY;
}
