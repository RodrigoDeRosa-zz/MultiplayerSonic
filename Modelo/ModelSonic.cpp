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

void ModelSonic::cortarSalto() {
    bloque_pers->cortarSalto();
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
	
	if (bloque_pers->estaDaniado() || (posX==DMG_ARG && posY==DMG_ARG)){
		bloque_pers->damage();
	}
	else if (bloque_pers->estaRodando() || (posX==ROLL_ARG && posY==ROLL_ARG)){
		bloque_pers->roll();
	}
    else if(vel_y< 0.0 || bloque_pers->estaSaltando()){
        jump(vel_x,vel_y);
    }
    else if(vel_x> 0.0){
        moveRight(vel_x);}
    else if(vel_x < 0.0){
        moveLeft(vel_x);}

        
    else{
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

void ModelSonic::setY(float new_y){
    bloque_pers->setY(new_y);
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
/*
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
*/
void ModelSonic::roll(){
	//bloque_pers->roll();
	//cambiamos por fruta magica para que llame a update
	this->update((bloque_pers->estaMirandoADer() ? 1.0 : -1.0),0.0,ROLL_ARG,ROLL_ARG);
}

void ModelSonic::lastimar(){
	this->update((bloque_pers->estaMirandoADer() ? 1.0 : -1.0),0.0,DMG_ARG,DMG_ARG);
}

void ModelSonic::stop(){
    this->direccionY=0;
    //this->direccionX=0;
    this->bloque_pers->setPosicionInicio();
}
