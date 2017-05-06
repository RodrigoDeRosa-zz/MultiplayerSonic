#include "CameraControl.hpp"
#include <stdio.h>

CameraControl::CameraControl(float width){
	this->width = width;
	this->position = 0;
	//todos los jugadores empiezan en el lado izquierdo de la pantalla
	this->playerOnLeftEdge = true;
	this->playerOnRightEdge = false;
}

float CameraControl::getLeftEdge(){
	return this->position;
}

float CameraControl::getRightEdge(){
	return this->position + width;
}

float CameraControl::getPosition(){
	return this->position;
}

bool CameraControl::validNewPosition(float newPosition, Model* model){
	//la camara se mueve para la derecha pero hay alguien en el limite izquierdo
	if((newPosition < 0) && (model->playerInPosition(this->getLeftEdge()))){
		return false;
	}
	//la camara se mueve para la izquierda pero hay alguien en el limite derecho
	else if((newPosition < this->getLeftEdge()) && (model->playerInPosition(this->getRightEdge()))){
		return false;
	}
	return true;
}

bool CameraControl::moveCamera(float newPosition,Model* model){
	newPosition = this->getRightEdge() - newPosition;
	if((newPosition <= this->getRightEdge()) && (newPosition >= this->getLeftEdge())){
		return true;
	}
	if(this->validNewPosition(newPosition,model)){
		this->position -= newPosition;
		return true;
	}
	return false;
}
