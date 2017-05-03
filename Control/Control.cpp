#include "Control.hpp"

#define VELOCITY 0.35
#define VEL -0.8

using namespace std;

Control::Control(){
	this->model = new Model();
	this->setCameraPosition(0);
}

void Control::addPlayer(string playerName){
	this->model->addPlayer(playerName);
}

void Control::setCameraPosition(float cameraPosition){
	this->cameraPosition = cameraPosition;
}

vector<float> Control::handleEvent(string playerName, SDL_Event e){
	this->setPlayerPosition(playerName,e);
	vector<float> playerVelocities = this->model->getPlayerVelocities(playerName);
	this->updateCamera(playerName);
	return playerVelocities; //la funcion va a ser void pero queda para probar
}

void Control::setPlayerPosition(string playerName, SDL_Event e){
	vector<float> playerVelocities = this->model->getPlayerVelocities(playerName);
	float velX = playerVelocities[0];
	float velY = playerVelocities[1];
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch( e.key.keysym.sym ){
			case SDLK_UP: velY = VEL; break;
			case SDLK_LEFT: velX -= VELOCITY; break;
			case SDLK_RIGHT: velX += VELOCITY; break;
		}
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
		switch( e.key.keysym.sym ){
			case SDLK_LEFT: velX += VELOCITY; break;
			case SDLK_RIGHT: velX -= VELOCITY; break;
		}
	}
	this->model->setPlayerPosition(playerName,velX,velY);
}

void Control::updateCamera(string playerName){
	vector<float> currentPlayerPosition = this->model->getPlayerPosition(playerName);
	if(this->cameraPosition > currentPlayerPosition[0]) return;
	this->setCameraPosition(currentPlayerPosition[0]);
}

