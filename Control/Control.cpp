#include "Control.hpp"
#include <stdio.h>
#include <sstream>

#define VELOCITY 0.35 //definidos como constantes pero lo mejor es pasarlos como parametro para que sea consistente con la vista
#define VEL -0.8

//int to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

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

vector<float> Control::getDirections(SDL_Event e,string playerName){
    vector<float> directions = this->model->getPlayerDirections(playerName);
    float dirX = directions[0];
    float dirY = directions[1];
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
	directions[0] = dirX;
    directions[1] = dirY;
	return directions;
}

vector<float> Control::getDirections(key_event e, string playerName){
    vector<float> directions = this->model->getPlayerDirections(playerName);
    float dirX = directions[0];
    float dirY = directions[1];
	switch( e ){
		case SPACE_DOWN: dirY -= 1; break;
		case LEFT_DOWN: dirX -= 1; break;
		case RIGHT_DOWN: dirX += 1; break;
		case SPACE_UP: dirY += 1; break;
		case LEFT_UP: dirX += 1; break;
		case RIGHT_UP: dirX -= 1; break;
	}
    directions[0] = dirX;
    directions[1] = dirY;
	return directions;
}

bool Control::moveCamera(float newPlayerX,string playerName){
	return 	(this->cameraControl->moveCamera(newPlayerX,this->model,playerName));
}

bool Control::moveCameraAndPlayer(string playerName, vector<float> directions){
	vector<float> previousPlayerPosition = this->model->getPlayerPosition(playerName);
	this->model->movePlayer(playerName,directions[0],directions[1]);
	vector<float> newPlayerPosition = this->model->getPlayerPosition(playerName);
	float previousCameraPosition = this->getCameraPosition();
	if(!(this->moveCamera(newPlayerPosition[0],playerName))){
	 	//si no puedo mover la camara vuelvo a setear la posicion anterior del jugador
	 	this->model->setPlayerPosition(playerName,previousPlayerPosition[0],previousPlayerPosition[1]);
	 	return false;
	}
	if(this->getCameraPosition() != previousCameraPosition) this->model->moveDisconnectedPlayers(this->cameraControl->getLeftEdge(),this->cameraControl->getRightEdge(),directions[0]);
	return true;
}

void Control::setPlayerConnection(string playerName, bool connection){
	this->model->setPlayerConnection(playerName,connection);
}

vector<float> Control::getPlayerPosition(string playerName){
	return this->model->getPlayerPosition(playerName);
}

void setOutMessage(out_message_t* message,char ping,int id,bool connection,float dirX,float dirY,float posX,float posY,float camPos){
	message->ping = ping;
	message->id = id;
	message->connection = connection;
	message->dirX = dirX;
	message->dirY = dirY;
	message->posX = posX;
	message->posY = posY;
	message->camPos = camPos;
}

vector<out_message_t*> Control::handleInMessage(in_message_t* ev){
	vector<out_message_t*> v;
	string playerName = SSTR(ev->id);
	out_message_t* message;
	vector<float> directions = this->getDirections(ev->key,SSTR(ev->id));
	setOutMessage(message,0,ev->id,true,directions[0],directions[1],0,0,this->getCameraPosition());
	if(!(this->moveCameraAndPlayer(playerName,directions))){
		message->dirX = 0;
		message->dirY = 0;
		v.push_back(message);
		return v;
	}
	message->camPos = this->getCameraPosition();
	v.push_back(message);
	vector<string> disconnectedPlayers = this->model->getDisconnectedPlayers();
	for(int i = 0; i < disconnectedPlayers.size(); i++){
		out_message_t* disconnectedMessage;
		vector<float> position = getPlayerPosition(disconnectedPlayers[i]);
		setOutMessage(disconnectedMessage,0,atoi(disconnectedPlayers[i].c_str()),false,0,0,position[0],position[1],this->getCameraPosition());
		v.push_back(disconnectedMessage);
	}
	return v;
}
