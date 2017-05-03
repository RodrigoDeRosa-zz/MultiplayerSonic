#include "Player.hpp"
#include <stdio.h>

Player::Player(string name){
	this->name = name;
	this->setX(0);
	this->setY(0);
	this->setVelX(0);
	this->setVelY(0);
	//printf()
}

string Player::getName(){
	return this->name;
}

float Player::getX(){
	return this->x;
}

float Player::getY(){
	return this->y;
}

void Player::setX(float x){
	this->x = x;
}

void Player::setY(float y){
	this->y = y;
}

float Player::getVelX(){
	return this->velX;
}

float Player::getVelY(){
	return this->velY;
}

void Player::setVelX(float velX){
	this->velX = velX;
}

void Player::setVelY(float velY){
	this->velY = velY;
}

void Player::updateX(float velX){
	this->setVelX(velX);
	this->setX(this->getX() + velX);
}

void Player::updateY(float velY){
	this->setVelY(velY);
	this->setY(this->getY() + velY);
}

void Player::updateXY(float velX,float velY){
	this->updateX(velX);
	this->updateY(velY);
}
