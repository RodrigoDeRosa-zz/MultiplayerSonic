#include "CameraControl.hpp"
#include <stdio.h>
#define MARGIN_FACTOR 0.25
#define CHARACTER_WIDTH 118

CameraControl::CameraControl(float width){
	this->width = width;
	this->position = 0;
	//todos los jugadores empiezan en el lado izquierdo de la pantalla
	this->playerOnLeftEdge = true;
	this->playerOnRightEdge = false;
}

float CameraControl::getLeftEdge(){
	return this->position + width*MARGIN_FACTOR;
}

float CameraControl::getRightEdge(){
	return this->position + width*(1-MARGIN_FACTOR);
}

float CameraControl::getPosition(){
	return this->position;
}

bool CameraControl::moveCameraLeft(float newPosition,Model* model){
	if(model->playerInPosition(this->getRightEdge())) return false;
	this->position = newPosition-(this->width*MARGIN_FACTOR);
	if(this->position < 0) this->position = 0;
	return true;
}

bool CameraControl::moveCameraRight(float newPosition,Model* model){
	if(model->playerInPosition(this->getLeftEdge())) return false;
	this->position = newPosition-(this->width*(1-MARGIN_FACTOR));
	return true;
}

bool CameraControl::moveCamera(float newPosition,Model* model){
	//printf("camera: %f\n player:%f \n\n", this->position,newPosition);
	if((newPosition <= this->getRightEdge()) && (newPosition >= this->getLeftEdge())){
		return true;
	}
	if(newPosition < this->getLeftEdge()) return this->moveCameraLeft(newPosition,model);
	return this->moveCameraRight(newPosition,model);
}
