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

vector<float> Control::handleEvent(string playerName, SDL_Event e,float dirX,float dirY){
	vector<float> directions = this->getDirections(e,dirX,dirY);
	if(!(this->moveCameraAndPlayer(playerName,directions))){
		directions[0] = 0;
		directions[1] = 0;
	}
	else this->model->moveDisconnectedPlayers(this->getDisconnectedPlayersNewPosition(directions[0]));
	//mandar directions posicion desconectados y cameraPosition a la vista
	 //la funcion va a ser void pero queda para probar

	return directions;
}

float Control::getCameraPosition(){
	this->cameraControl->getPosition();
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

bool Control::moveCamera(float newPlayerX){
	return 	(this->cameraControl->moveCamera(newPlayerX,this->model));
}

bool Control::moveCameraAndPlayer(string playerName, vector<float> directions){
	 vector<float> previousPlayerPosition = this->model->getPlayerPosition(playerName);
	this->model->movePlayer(playerName,directions[0],directions[1]);
	 vector<float> newPlayerPosition = this->model->getPlayerPosition(playerName);
	 if(!(this->moveCamera(newPlayerPosition[0]))){
	// 	//si no puedo mover la camara vuelvo a setear la posicion anterior del jugador
	 	this->model->setPlayerPosition(playerName,previousPlayerPosition[0],previousPlayerPosition[1]);
	 	return false;
	}
	return true;
}

float Control::getDisconnectedPlayersNewPosition(float dirX){
	if (dirX > 0) return this->cameraControl->getLeftEdge();
	return this->cameraControl->getRightEdge();
}
