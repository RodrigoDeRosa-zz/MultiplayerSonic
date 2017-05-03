#include "CameraControl.hpp"

CameraControl::CameraControl(float width){
	this->width = width;
	this->position = width;
	//todos los jugadores empiezan en el lado izquierdo de la pantalla
	this->playerOnLeftEdge = true;
	this->playerOnRightEdge = false;
}

float CameraControl::getLeftEdge(){
	return this->position - (this->width);
}

float CameraControl::getRightEdge(){
	return this->position;
}

bool CameraControl::validNewPosition(float newPosition){
	//limite izquierdo del escenario
	if(newPosition < 0) return false;
	//la camara se mueve para la derecha pero hay alguien en el limite izquierdo
	else if((newPosition > this->getRightEdge()) && (this->playerOnLeftEdge)){
		return false;
	}
	//la camara se mueve para la izquierda pero hay alguien en el limite derecho
	else if((newPosition < this->getLeftEdge()) && (this->playerOnRightEdge)){
		this->position = newPosition;
		return false;
	}
	return true;
}

bool CameraControl::moveCamera(float newPosition){
	if(this->validNewPosition(newPosition)){
		this->position = newPosition;
		return true;
	}
	return false;
}

