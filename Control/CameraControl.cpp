#include "CameraControl.hpp"
#include <stdio.h>
#define MARGIN_FACTOR 0.01
#define CHARACTER_WIDTH 118

CameraControl::CameraControl(float width){
	this->width = width;
	this->position = 0;
}

float CameraControl::getLeftEdge(){
	return this->position + width*MARGIN_FACTOR;
}

float CameraControl::getRightEdge(){
	return this->position + width*(1-MARGIN_FACTOR) - CHARACTER_WIDTH;
}

float CameraControl::getPosition(){
	return this->position;
}

bool CameraControl::moveCameraLeft(float newPosition,Model* model,string playerName){
	if(model->otherPlayerInPosition(playerName,this->getRightEdge(),false)){
		return false;
	}
	this->position = newPosition-(this->width*MARGIN_FACTOR);
	if(this->position < 0) this->position = 0;
	return true;
}

bool CameraControl::moveCameraRight(float newPosition,Model* model, string playerName){
	if(model->otherPlayerInPosition(playerName,this->getLeftEdge(),true)){
		return false;
	}
	this->position = newPosition-(this->width*(1-MARGIN_FACTOR))+CHARACTER_WIDTH;
	if(this->position < 0) this->position = 0;
	return true;
}

bool CameraControl::playerInCameraRange(float playerPosition){
	if((playerPosition < this->getRightEdge()) && (playerPosition > this->getLeftEdge())){
		return true;
	}
	return false;
}

bool CameraControl::moveCamera(float newPosition,Model* model, string playerName, float dirX){
	if(this->playerInCameraRange(newPosition)){
		return true;
	}
	if((dirX < 0) && (newPosition <= this->getLeftEdge())) return this->moveCameraLeft(newPosition,model,playerName);
	else if((dirX > 0) && (newPosition >= this->getRightEdge())) return this->moveCameraRight(newPosition,model,playerName);
	return true;
}
