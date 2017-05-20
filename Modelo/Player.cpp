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
	ModelSonic* sonic = new ModelSonic();
	this->sonic = sonic;
	this->setConnected(true);
    this->cargarMapCollitionBoxes();
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
	this->sonic->update(this->getDirX(),this->getDirY());
	this->sonic->setX(x);
}

void Player::setY(float y){
	this->sonic->update(this->getDirX(),this->getDirY(),this->getX(),y);
}

void Player::updateXY(float dirX,float dirY){
	this->sonic->update(dirX,dirY);
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

void Player::setXY(float x, float y){
	this->sonic->update(0,0,x,y);
}

void Player::aplicarEfecto(Efecto* efecto){
	string atributo = efecto->getAtributo(); //hacer lo que haga falta con atributo
	int cantidad = efecto->getCantidad(); //hacer lo que haga falta con entidad
}

float Player::getBordeDer(){

    return this->getX() + (this->collitionBoxes[this->getMovement()][0]);
}

float Player::getBordeIzq(){

    return this->getX() - (this->collitionBoxes[this->getMovement()][0]);
}

float Player::getBordeArriba(){

    return this->getY() + (this->collitionBoxes[this->getMovement()][1]);
}

float Player::getBordeAbajo(){

    return this->getY();
}

void Player::cargarMapCollitionBoxes(){

    //El h hay que cambiarlo a medida que vayamos ajustando
    //las colisiones

    vector<float> quieto;
    quieto.push_back(97);
    quieto.push_back(121);
    this->collitionBoxes[IDLED] = quieto;
    this->collitionBoxes[IDLEI] = quieto;

    vector<float> jump;
    jump.push_back(97);
    jump.push_back(121);
    this->collitionBoxes[JUMPI] = jump;
    this->collitionBoxes[JUMPD] = jump;

    vector<float> run;
    run.push_back(97);
    run.push_back(121);
    this->collitionBoxes[RUNI] = run;
    this->collitionBoxes[RUND] = run;

    vector<float> caminar;
    caminar.push_back(100);
    caminar.push_back(121);
    this->collitionBoxes[WALKI] = caminar;
    this->collitionBoxes[WALKD] = caminar;

    //en el futuro agregar el resto de los movimientos
}

float Player::getCentroX(){
    return this->getX() + (this->collitionBoxes[this->getMovement()][0] / 2);
}

float Player::getCentroY(){
    return this->getY() + (this->collitionBoxes[this->getMovement()][1] / 2);
}

void Player::afectarseCon(Entidad* entidad){

    //calculo de la colision mas meticuloso que el rango

    float centroEntX = entidad->getCentroX();
    float centroPlayX = this->getCentroX();
    float centroEntY = entidad->getCentroY();
    float centroPlayY = this->getCentroY();

    float bordeDerE = entidad-> getBordeDer();
    float bordeIzqE = entidad-> getBordeIzq();

    float bordeDerP = this-> getBordeDer();
    float bordeIzqP = this-> getBordeIzq();

    float bordeArribaE = entidad -> getBordeArriba();
    float bordeArribaP = this -> getBordeArriba();

    float bordeAbajoE = entidad -> getBordeAbajo();
    float bordeAbajoP = entidad-> getBordeAbajo();

    //agregar factores para retocar con mas presicion
    bool colisionX = ((bordeDerP > bordeIzqE) || (bordeDerE > bordeIzqP));
    bool contactoX = ((bordeDerP >= bordeIzqE) || (bordeDerE >= bordeIzqP));

    bool colisionY = ((bordeArribaP > bordeAbajoE) || (bordeArribaE > bordeAbajoP));
    bool contactoY = ((bordeArribaP >= bordeAbajoE) || (bordeArribaE >= bordeAbajoP));

    //CALCULO DE COLISIONES BASICAS CON 2 SPRITES RECTANGULARES.
    if (colisionX && contactoY){
        this->aplicarEfecto(entidad->getEfecto());
    }
    else if(colisionY && contactoX){
        this->aplicarEfecto(entidad->getEfecto());
    }
}
