#include "Player.hpp"
#define RUNNNING_EVENTS 1000
#define RUNNING_VELOCITY 0.7
#define EVENT_UNIT 1
#define JUMPING_EVENTS -12
#define MOVEMENT_CONTROL 0.001
#define GRAVITY 0.5

Player::Player(string name){
	this->name = name;
	this->setX(0);
	this->setY(0);
	this->vel = 0.35;
	this->eventCounterX = 0;
	this->eventCounterY = 0;
	this->eventCounterJump = 0;
	this->jumping = false;
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

void Player::moveX(float dirX){
	eventCounterX += EVENT_UNIT*dirX;
	if(this->eventCounterX == RUNNNING_EVENTS*dirX) this->x += (this->vel + RUNNING_VELOCITY)*dirX;
	else this->x += this->vel*dirX;
}

void Player::stop(){
	this->eventCounterX == 0;
	this->eventCounterY == 0;
	this->eventCounterJump == 0;
}

void Player::updateXY(float dirX,float dirY){
	// convierto dirX y dirY en +- 1
	
	if(dirX) dirX /= dirX;
	if(dirY)dirY /= dirY;
	
	if(dirY < 0.0 || this->jumping) jump(dirX);
  	else if((dirX == 0) && (dirY == 0)) this->stop();
  	else this->moveX(dirX);
}

void Player::jump(float dirX){
  if(eventCounterY == 0 && not jumping){
    eventCounterY = JUMPING_EVENTS;
    jumping = true;
  }
  float velH = 0;
  if(dirX > 0){
    jumpRight(&velH);
  }
  else if(dirX < 0){
    jumpLeft(&velH);
  }
  this->x += 3*(velH * eventCounterJump);
  this->y += (1.5)*(eventCounterY * eventCounterJump);
  eventCounterY += (GRAVITY * eventCounterJump);

  eventCounterJump += MOVEMENT_CONTROL;

  //Este chequeo se hace para que vuelva a empezar de 0 el salto.
  if(eventCounterY >= (JUMPING_EVENTS*-1) && jumping){
    eventCounterJump = 0.0;
    jumping = false;
    eventCounterY = 0.0;
  }
}
  
void Player::jumpLeft(float* velH){
  *velH = (this->vel)*(-5);
  if(eventCounterX <= -RUNNNING_EVENTS){
    *velH -= RUNNING_VELOCITY*2;
  }
  if((this->x)<0) this->x = 0;
}

void Player::jumpRight(float* velH){
    *velH = (this->vel)*5;
    if(eventCounterX >= RUNNNING_EVENTS){
      *velH += RUNNING_VELOCITY*2;
    }
    //chequear no pasarse del escenario
}

