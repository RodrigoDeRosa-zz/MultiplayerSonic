#include "Control.hpp"

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

vector<float> Control::handleEvent(string playerName, SDL_Event e){
	this->movePlayerAndCamera(playerName,e);
	vector<float> playerVelocities = this->model->getPlayerVelocities(playerName);
	//mandar velocities y cameraPosition a la vista
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
	this->model->updatePlayerPosition(playerName,velX,velY);
}

void Control::movePlayerAndCamera(string playerName, SDL_Event e){
	vector<float> previousPlayerPosition = this->model->getPlayerPosition(playerName);
	vector<float> previousPlayerVelocities = this->model->getPlayerVelocities(playerName);
	this->setPlayerPosition(playerName,e);
	vector<float> newPlayerPosition = this->model->getPlayerPosition(playerName);
	// si no se puede mover la camara, el jugador vuelve a la posicion y velocidad anterior	
	if(!(this->cameraControl->moveCamera(newPlayerPosition[0]))){
		this->model->setPlayerPosition(playerName,previousPlayerPosition[0],previousPlayerPosition[1]);
		this->model->setPlayerVelocities(playerName,previousPlayerVelocities[0],previousPlayerVelocities[1]);
	}	
}

