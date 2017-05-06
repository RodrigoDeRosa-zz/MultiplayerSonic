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

bool CameraControl::validNewPosition(float newPosition, Model* model){
	//limite izquierdo del escenario
	if(newPosition < 0) return false;
	//la camara se mueve para la derecha pero hay alguien en el limite izquierdo
	else if((newPosition > this->getRightEdge()) && !(model->playerInPosition(this->getLeftEdge()))){
		return false;
	}
	//la camara se mueve para la izquierda pero hay alguien en el limite derecho
	else if((newPosition < this->getLeftEdge()) && !(model->playerInPosition(this->getRightEdge()))){
		return false;
	}
	return true;
}

bool CameraControl::moveCamera(float newPosition,Model* model){
	if((newPosition <= this->position) && (newPosition >= this->getLeftEdge())) return true;
	if(this->validNewPosition(newPosition,model)){
		this->position = newPosition;
		return true;
	}
	return false;
}

