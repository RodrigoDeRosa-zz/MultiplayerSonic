#include "Player.hpp"
#define RUNNNING_EVENTS 1000
#define RUNNING_VELOCITY 0.7
#define EVENT_UNIT 1
#define JUMPING_EVENTS -12
#define MOVEMENT_CONTROL 0.001
#define GRAVITY 0.5

Player::Player(string name, Sonic* sonic){
	this->name = name;
	this->vel = 0.35;
	this->eventCounterX = 0;
	this->eventCounterY = 0;
	this->eventCounterJump = 0;
	this->jumping = false;
	this->connected = true;
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

void Player::setX(float x){
	this->sonic->update(0,0,x,this->getY());
}

void Player::setY(float y){
	this->sonic->update(0,0,this->getX(),y);
}

void Player::updateXY(float dirX,float dirY){
	// convierto dirX y dirY en +- 1

	this->sonic->update(dirX,dirY);
	printf("%f\n", this->getX());
}

bool Player::isConnected(){
    return this->connected;
}

void Player::setConnected(bool connected){
    this->connected = connected;
}
