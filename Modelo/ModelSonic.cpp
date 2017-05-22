#include "ModelSonic.hpp"
using namespace std;

#define WALKING_ANIMATION_FRAMES 6
#define FACTOR 8


ModelSonic::ModelSonic(){
    bloque_pers = new MoveSonic(100.0, 300.0);
    frameRight = 0;
    frameLeft = 0;
    direccionX = 0.0;
    direccionY = 0.0;
}

/*Funciones de movimiento*/
void ModelSonic::update(float vel_x, float vel_y, float posX, float posY){

    if(vel_x >= 1.0){
        vel_x = 1.0;
    }

    else if(vel_x <= -1.0){
        vel_x = -1.0;
    }

    if(vel_y <= -1.0){
        vel_y = -1.0;
    }
    else if(vel_y > 0.0){
        vel_y = 0.0;
    }

    if(vel_y< 0.0 || bloque_pers->estaSaltando()){
        jump(vel_x,vel_y);
    }
    else if(vel_x> 0.0){
        moveRight(vel_x);}
    else if(vel_x < 0.0){
        moveLeft(vel_x);}

        //si no se movio para ningun seteamos las velocidades y frames a 0
    else{//MARTIN: creo que por esta cosa nunca llega a frenar, soltas las teclas e impone el IDLE
        bloque_pers->setPosicionInicio();
    }

    //si no se pasa una posicion al update, este no la modifica
    if(posX >= 0){
        bloque_pers->update(posX, posY);
    }

    direccionX = vel_x;
    direccionY = vel_y;
}

void ModelSonic::setX(float new_x){
    bloque_pers->setX(new_x);
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

void ModelSonic::crouch(){
	//if velocidadX!=0 o velocidadY!=0 return
	this->bloque_pers->crouch();
}

void ModelSonic::release(){
	//if charges==0 setPosicionInicio() y return
	this->bloque_pers->release();
}

void ModelSonic::charge(){
	this->bloque_pers->charge();
}
