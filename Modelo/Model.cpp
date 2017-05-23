#include "Model.hpp"
#include "Entidades/Piedra.hpp"
#include <stdio.h>

Model::Model(){
	players = new vector<Player*>();
	entidades = new vector<Entidad*>();
	Piedra* piedra = new Piedra(500, 298, 200, 200);
	entidades->push_back(piedra);
}

void Model::addPlayer(string playerName){
	Player* player = new Player(playerName);
	(this->players)->push_back(player);
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

//	float centroEnt = entidad->getCentroX();
//	float centroPlay = player->getCentroX();

	float bordeDerE = entidad->getBordeDer();
	float bordeIzqE = entidad->getBordeIzq();

	float bordeDerP = player->getBordeDer();
	float bordeIzqP = player->getBordeIzq();

	return ((bordeDerP == bordeIzqE) || (bordeDerE == bordeIzqP));

//	if((((*entidades)[j]->getX() >= (*players)[i]->getX()) && ((*entidades)[j]->getX() <= ((*players)[i]->getX() + 118.0)))
//	   ||
//	   (((*entidades)[j]->getBordeDer() >= (*players)[i]->getX()) && ((*entidades)[j]->getBordeDer() <= ((*players)[i]->getX() + 118)))
//		/*||
//        (((*players)[i])->getBordeAbajo() >= (*entidades)[j]->getBordeArriba()) este ultimo chequeo rompe todo pero hay que hacerlo de alguna forma*/){
//
}

void Model::colisionarTodos(){
	for(int i = 0; i < (players)->size(); i++){
		for(int j = 0; j < (entidades)->size(); j++){

			if (this->enRango((*entidades)[j], (*players)[i])){
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
