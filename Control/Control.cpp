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
    k = 0;
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

vector<float> Control::getDirections(key_event e, string playerName){
	vector<float> directions = this->model->getPlayerDirections(playerName);
	float dirX = directions[0];
	float dirY = directions[1];
	switch( e ){
		case QUIT: this->model->setPlayerConnection(playerName,false); break;
        case RECONNECTION: this->model->setPlayerConnection(playerName, true); break;
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
	 	this->model->setPlayerPosition(playerName,previousPlayerPosition[0]);
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

void setOutMessage(out_message_t* message,char ping,int id,bool connection,int frame,move_type move,float posX,float posY,float camPos){
	message->ping = ping;
	message->id = id;
	message->connection = connection;
	message->posX = posX;
	message->posY = posY;
	message->frame = frame;
	message->move = move;
	message->camPos = camPos;
}

void Control::handleInMessage(in_message_t* ev){
	string playerName = SSTR(ev->id);
	//obtengo las direcciones en base al key event
	vector<float> directions = this->getDirections(ev->key,SSTR(ev->id));
	//muevo el jugador y la camara con las direcciones obtenidas
	this->model->movePlayer(playerName,directions[0],directions[1]);
}

void Control::update(){
	vector<string> players = this->model->getPlayerNames();
	for(int i=0; i < players.size(); i++){
		vector<float> directions = this->model->getPlayerDirections(players[i]);
		this->moveCameraAndPlayer(players[i],directions);
	}
}

vector<out_message_t*> Control::getStatus(){
	vector<out_message_t*> v;
	vector<string> players = this->model->getPlayerNames();
	for(int i=0; i < players.size(); i++){
		out_message_t* message = new out_message_t;
		vector<float> playerPosition = this->model->getPlayerPosition(players[i]);
		vector<float> directions = this->model->getPlayerDirections(players[i]);
		//this->moveCameraAndPlayer(players[i],directions);
		vector<float> newPlayerPosition = this->model->getPlayerPosition(players[i]);
        if (k < 10){
            if((playerPosition[0] == newPlayerPosition[0]) && (playerPosition[1] == newPlayerPosition[1])){
                k++;
                continue;
            }
        }
        k = 0;
		setOutMessage(message,0,atoi(players[i].c_str()),this->model->playerIsConnected(players[i]),this->model->getPlayerFrame(players[i]),this->model->getPlayerMovement(players[i]),
						playerPosition[0],playerPosition[1],this->getCameraPosition());
		v.push_back(message);
	}
	return v;
}
