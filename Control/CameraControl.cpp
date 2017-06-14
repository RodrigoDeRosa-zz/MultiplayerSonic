#include "CameraControl.hpp"
#include <stdio.h>
#define RIGHT_MARGIN_FACTOR 0.11
#define LEFT_MARGIN_FACTOR 0.05
#define CHARACTER_WIDTH 118

CameraControl::CameraControl(float width, float stageEnd){
	this->width = width;
	this->position = 0;
	this->stageEnd = stageEnd;
}

float CameraControl::getLeftEdge(){
	return this->position + width*LEFT_MARGIN_FACTOR;
}

float CameraControl::getRightEdge(){
	return this->position + width*(1-RIGHT_MARGIN_FACTOR) - CHARACTER_WIDTH;
}

float CameraControl::getPosition(){
	return this->position;
}

bool CameraControl::moveCameraLeft(float newPosition,Nivel* model,string playerName){
	if(model->otherPlayerInPosition(playerName,this->getRightEdge(),false)){
		return false;
	}
	this->position = newPosition-(this->width*LEFT_MARGIN_FACTOR);
	if(this->position < 0) this->position = 0;
	return true;
}

bool CameraControl::moveCameraRight(float newPosition,Nivel* model, string playerName){
	if(model->otherPlayerInPosition(playerName,this->getLeftEdge(),true)){
		return false;
	}
	this->position = newPosition-(this->width*(1-RIGHT_MARGIN_FACTOR))+CHARACTER_WIDTH;
	if(this->position < 0) this->position = 0;
	else if((this->position + this->width) >= this->stageEnd) this->position = this->stageEnd - this->width;
	return true;
}

bool CameraControl::playerInCameraRange(float playerPosition){
	if((playerPosition < this->getRightEdge()) && (playerPosition > this->getLeftEdge())){
		return true;
	}
	return false;
}

bool CameraControl::moveCamera(float newPosition,Nivel* model, string playerName, float dirX){
	if(this->playerInCameraRange(newPosition)){
		return true;
	}
	if((this->position >= 4800) && ((dirX < 0) && (newPosition <= this->getLeftEdge()))) return false;
	if((this->position >= 4800) && (model->getPlayer(playerName)->estaAtacando()) && (newPosition <= this->getLeftEdge())) return false;
	if((dirX < 0) && (newPosition <= this->getLeftEdge())) return this->moveCameraLeft(newPosition,model,playerName);
	if((dirX > 0) && (newPosition >= this->getRightEdge())) return this->moveCameraRight(newPosition,model,playerName);
	if((model->getPlayer(playerName)->estaAtacando()) && (newPosition <= this->getLeftEdge())) return this->moveCameraLeft(newPosition,model,playerName);
	if((model->getPlayer(playerName)->estaAtacando()) && (newPosition >= this->getRightEdge())) return this->moveCameraRight(newPosition,model,playerName);
	
	return true;
}

void CameraControl::reset(float stageEnd){
	this->position = 0;
	this->stageEnd = stageEnd;
}
