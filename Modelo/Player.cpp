#include "Player.hpp"
#include <stdio.h>
#define RUNNNING_EVENTS 1000
#define RUNNING_VELOCITY 0.7
#define EVENT_UNIT 1
#define JUMPING_EVENTS -12
#define MOVEMENT_CONTROL 0.001
#define GRAVITY 0.5

Player::Player(string name){
	this->name = name;
	ModelSonic* sonic = new ModelSonic(100,300);
	this->sonic = sonic;
}

string Player::getName(){
	return this->name;
}

float Player::getX(){
	return this->sonic->getX();
}

float Player::getY(){
	return this->sonic->getY();
}

float Player::getDirX(){
	return this->sonic->getDirX();
}

float Player::getDirY(){
	return this->sonic->getDirY();
}

void Player::setX(float x){
	this->sonic->update(0,0,x,this->getY());
}

void Player::setY(float y){
	this->sonic->update(0,0,this->getX(),y);
}

void Player::updateXY(float dirX,float dirY){
	this->sonic->update(dirX,dirY);
	printf("Nombre Jugador en Control: %s \n",this->getName().c_str());
	printf("Posicion en Control despues de actualizar: x=%f y=%f \n",this->getX(),this->getY());
}

bool Player::isConnected(){
    return this->connected;
}

void Player::setConnected(bool connected){
    this->connected = connected;
}

move_type Player::getMovement(){
	return this->sonic->getMovement();
}

int Player::getFrame(){
	return this->sonic->getFrame();
}
