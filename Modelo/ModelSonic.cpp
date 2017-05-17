#include "ModelSonic.hpp"

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8
using namespace std;



ModelSonic::ModelSonic{
    bloque_pers = NULL;
    frameRight = 0;
    frameLeft = 0;
    direccionX = 0.0;
    direccionY = 0.0;
}

/*setters*/
void ModelSonic::setMoveSonic(MoveSonic* new_bloque){
    bloque_pers = new_bloque;
}

/*Funciones de movimiento*/
void ModelSonic::update(float vel_x, float vel_y, float posX, float posY){
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

void ModelSonic::moveRight(float vel_x){
    bloque_pers->moveRight(vel_x);
}

void ModelSonic::moveLeft(float vel_x){
    bloque_pers->moveLeft(vel_x);
}

void ModelSonic::jump(float vel_x, float vel_y){
    bloque_pers->jump(vel_x,vel_y);
}

float ModelSonic::getX(){
    return bloque_pers->getX();
}

float ModelSonic::getY(){
    return bloque_pers->getY();
}

float ModelSonic::getDirX(){
    return direccionX;
}

float ModelSonic::getDirY(){
    return direccionY;
}

int ModelSonic::getFrame(){
    return bloque_pers->getFrame();
}

move_type ModelSonic::getMovement(){
    return bloque_pers->getMovement();
}
