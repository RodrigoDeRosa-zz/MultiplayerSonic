#include "Model.hpp"
#include "Entidades/Piedra.hpp"
#include <stdio.h>

Model::Model(){
	players = new vector<Player*>();
	entidades = new vector<Entidad*>();
	this->playerStatusControl = 0;
	this->entidadesStatusControl = 0;
}

void Model::addPlayer(string playerName){
	Player* player = new Player(playerName);
	(this->players)->push_back(player);
}

void Model::addEntidad(Entidad* entidad){
	(this->entidades)->push_back(entidad);
}

Player* Model::getPlayer(string nombre){
	for(int i = 0; i < players->size(); i++){
		if(((*players)[i])->getName() == nombre){
			return (*players)[i];
		}
	}
	return NULL;
}

void Model::setPlayerPosition(string playerName, float x){
	Player* player = this->getPlayer(playerName);
	player->setX(x);
}

void Model::movePlayer(string playerName, float dirX, float dirY){
	Player* player = this->getPlayer(playerName);
	player->updateXY(dirX,dirY);
}

vector<float> Model::getPlayerPosition(string playerName){
	vector<float> position;
	Player* player = this->getPlayer(playerName);
	position.push_back(player->getX());
	position.push_back(player->getY());
	return position;
}

vector<float> Model::getPlayerDirections(string playerName){
	vector<float> directions;
	Player* player = this->getPlayer(playerName);
	directions.push_back(player->getDirX());
	directions.push_back(player->getDirY());
	return directions;
}

bool Model::otherPlayerInPosition(string playerName,float position, bool left){
	for(int i = 0; i < players->size(); i++){
		if((*players)[i]->getName() == playerName){
			continue;
		}
		if(!((*players)[i]->isConnected())){
			continue;
		}
		//el jugador esta a la izquierda de la posicion
		if((left) && ((*players)[i]->getX() <= position)){
			return true;
		}
		//el jugador esta a la derecha de la posicion
		if(!(left) && ((*players)[i]->getX() >= position)) {
			return true;
		}
	}
	return false;
}

void Model::moveDisconnectedPlayers(float cameraLeftEdge,float cameraRightEdge,float dirX){
	for(int i = 0; i < players->size(); i++){
		if(!((*players)[i]->isConnected())){
			vector<float> playerPosition = this->getPlayerPosition((*players)[i]->getName());
			if(dirX > 0){
				if(playerPosition[0] < cameraLeftEdge) (*players)[i]->setX(cameraLeftEdge);
			}
			else if(dirX < 0){
				if(playerPosition[0] > cameraRightEdge) (*players)[i]->setX(cameraRightEdge);
			}
		}
	}
}

void Model::setPlayerConnection(string playerName, bool connection){
	Player* player = this->getPlayer(playerName);
	player->setConnected(connection);
}

vector<string> Model::getDisconnectedPlayers(){
	vector<string> names;
	for(int i = 0; i < players->size(); i++){
		if(!((*players)[i]->isConnected())) names.push_back((*players)[i]->getName());
	}
	return names;
}

move_type Model::getPlayerMovement(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->getMovement();
}

int Model::getPlayerFrame(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->getFrame();
}

vector<string> Model::getPlayerNames(){
	vector<string> v;
	for(int i = 0; i < this->players->size(); i++){
		v.push_back((*(this->players))[i]->getName());
	}
	return v;
}

bool Model::playerIsConnected(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->isConnected();
}

bool Model::enRango(Entidad* entidad, Player* player){

	float bordeDerE = entidad->getBordeDer();
	float bordeIzqE = entidad->getBordeIzq();

	float bordeDerP = player->getBordeDer();
	float bordeIzqP = player->getBordeIzq();

	return ((bordeDerP == bordeIzqE) || (bordeDerE == bordeIzqP));
}

void Model::colisionarTodos(){
	for(int i = 0; i < (players)->size(); i++){
		for(int j = 0; j < (entidades)->size(); j++){
			if((*entidades)[j]->estaDestruida()) continue;
			if ((*players)[i]->enRango((*entidades)[j])){
				(*players)[i]->afectarseCon((*entidades)[j]);
			}
		}
	}
}

void Model::playerCrouch(string playerName){
	Player* player = this->getPlayer(playerName);
	player->crouch();
}

void Model::playerCharge(string playerName){
	Player* player = this->getPlayer(playerName);
	player->charge();
}

void Model::playerRelease(string playerName){
	Player* player = this->getPlayer(playerName);
	player->release();
}

vector<out_message_t*> Model::getPlayerStatus(float camPos){
	vector<out_message_t*> v;
	for(int i=0; i < (this->players)->size(); i++){
		if (this->playerStatusControl < 10){
            this->playerStatusControl++;
            continue;
        }
        this->playerStatusControl = 0;
		v.push_back((*(this->players))[i]->getStatus(camPos));
	}
	return v;
}

vector<out_message_t*> Model::getEntidadesStatus(){
	vector<out_message_t*> v;
	for(int i=0; i < (this->entidades)->size(); i++){
		if (this->entidadesStatusControl < 10){
            this->entidadesStatusControl++;
            continue;
        }
        this->entidadesStatusControl = 0;
		v.push_back((*(this->entidades))[i]->getOutMessage());
	}
	return v;
}


vector<out_message_t*> Model::getStatus(float camPos){
	vector<out_message_t*> playerVector = this->getPlayerStatus(camPos);
	vector<out_message_t*> entidadesVector = this->getEntidadesStatus();
	playerVector.insert(playerVector.end(),entidadesVector.begin(),entidadesVector.end());
	return playerVector;
}

void Model::moverEntidades(){
	for(int i = 0; i < this->entidades->size(); i++){
		(*(this->entidades))[i]->mover();
	}
}