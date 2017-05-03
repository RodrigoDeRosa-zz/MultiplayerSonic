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

void Model::setPlayerPosition(string playerName, float velX, float velY){
	Player* player = this->getPlayer(playerName);
	player->updateXY(velX,velY);
}

vector<float> Model::getPlayerVelocities(string playerName){
	vector<float> velocities;
	Player* player = this->getPlayer(playerName);
	velocities.push_back(player->getVelX());
	velocities.push_back(player->getVelY());
	return velocities;
}

vector<float> Model::getPlayerPosition(string playerName){
	vector<float> position;
	Player* player = this->getPlayer(playerName);
	position.push_back(player->getX());
	position.push_back(player->getY());
	return position;
}
