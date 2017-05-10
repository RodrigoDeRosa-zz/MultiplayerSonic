#include "Control.hpp"
#include <stdio.h>

#define VELOCITY 0.35 //definidos como constantes pero lo mejor es pasarlos como parametro para que sea consistente con la vista
#define VEL -0.8

using namespace std;

Control::Control(){
	this->model = new Model();
	this->cameraControl = new CameraControl(1200); //el ancho de la camara tambien tiene que venir por parametro
}

void Control::addPlayer(string playerName){
	this->model->addPlayer(playerName);
}

float Control::getCameraPosition(){
	return this->cameraControl->getPosition();
}

vector<float> Control::getDirections(SDL_Event e, float dirX, float dirY){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch( e.key.keysym.sym ){
			case SDLK_SPACE: dirY -= 1; break;
			case SDLK_LEFT: dirX -= 1; break;
			case SDLK_RIGHT: dirX += 1; break;
		}
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0){
		switch( e.key.keysym.sym ){
			case SDLK_SPACE: dirY += 1; break;
			case SDLK_LEFT: dirX += 1; break;
			case SDLK_RIGHT: dirX -= 1; break;
		}
	}
	vector<float> directions;
	directions.push_back(dirX);
	directions.push_back(dirY);
	return directions;
}

bool Control::moveCamera(float newPlayerX,string playerName){
	return 	(this->cameraControl->moveCamera(newPlayerX,this->model,playerName));
}

bool Control::moveCameraAndPlayer(string playerName, vector<float> directions){
	vector<float> previousPlayerPosition = this->model->getPlayerPosition(playerName);
	this->model->movePlayer(playerName,directions[0],directions[1]);
	vector<float> newPlayerPosition = this->model->getPlayerPosition(playerName);
	if(!(this->moveCamera(newPlayerPosition[0],playerName))){
	 	//si no puedo mover la camara vuelvo a setear la posicion anterior del jugador
	 	this->model->setPlayerPosition(playerName,previousPlayerPosition[0],previousPlayerPosition[1]);
	 	return false;
	}
	this->model->moveDisconnectedPlayers(this->getCameraPosition(),directions[0]);
	return true;
}

void Control::setPlayerConnection(string playerName, bool connection){
	this->model->setPlayerConnection(playerName,connection);
}

vector<float> Control::getPlayerPosition(string playerName){
	return this->model->getPlayerPosition(playerName);
}