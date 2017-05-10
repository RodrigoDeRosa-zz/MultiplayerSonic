#include "Model.hpp"


Model::Model(){
	players = new vector<Player*>();
	segaFactory = new SegaFactory();
}

void Model::addPlayer(string playerName){
	Player* player = new Player(playerName, this->segaFactory->getSonic(playerName));
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

void Model::setPlayerPosition(string playerName, float x, float y){
	Player* player = this->getPlayer(playerName);
	player->setX(x);
	player->setY(y);
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

bool Model::otherPlayerInPosition(string playerName,float position, bool left){
	for(int i = 0; i < players->size(); i++){
		if((*players)[i]->getName() == playerName){
			continue;
		}
		if(!((*players)[i]->isConnected())){
			continue;
		}
		//el jugador esta a la izquierda de la posicion
		if((left) && ((*players)[i]->getX() < position)) return true;
		//el jugador esta a la derecha de la posicion
		if(!(left) && ((*players)[i]->getX() > position)) return true;
	}
	return false;
}

void Model::moveDisconnectedPlayers(float position,float dirX){
	for(int i = 0; i < players->size(); i++){
		if(!((*players)[i]->isConnected())){
			vector<float> playerPosition = this->getPlayerPosition((*players)[i]->getName());
			if((dirX > 0) && (playerPosition[0] < position))
				(*players)[i]->setX(position);
			else if((dirX < 0) && (playerPosition[0] > position))
				(*players)[i]->setX(position);
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
