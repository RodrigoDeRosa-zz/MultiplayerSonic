#include "Model.hpp"

Model::Model(){
	players = new vector<Player*>();
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

bool Model::playerInPosition(float position){
	for(int i = 0; i < players->size(); i++){
		if((*players)[i]->getX() == position) return true;
	}
	return false;
}
