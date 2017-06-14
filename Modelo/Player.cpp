#include "Player.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RUNNNING_EVENTS 1000
#define RUNNING_VELOCITY 0.7
#define EVENT_UNIT 1
#define JUMPING_EVENTS -12
#define MOVEMENT_CONTROL 0.001
#define GRAVITY 0.5

using namespace std;

Player::Player(string name, Puntaje* p){
	this->name = name;
	ModelSonic* sonic = new ModelSonic();
	this->sonic = sonic;
	this->setConnected(true);
    this->cargarMapCollitionBoxes();
    this->monedas = 0;
    this->vidas = 3;
	this->puntaje = p;
    this->estado = new Estado();
	this->atEnd = false;
	this->scoreIndiv = 0;
    this->vivo = true;
    this->frameMuerto = 0;
	this->frameSum = 0;
}

bool Player::estaVivo(){
    return this->vivo;
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

vector<float> Player::getDirections(){
    vector<float> directions;
    directions.push_back(this->getDirX());
    directions.push_back(this->getDirY());
    return directions;
}

void Player::setX(float x){
	this->sonic->update(this->getDirX(),this->getDirY());
	this->sonic->setX(x);
}

void Player::setY(float y){
    // si el jugador viene saltando hago que se detenga
    if((this->getMovement() == JUMPD) || (this->getMovement() == JUMPI)) this->sonic->cortarSalto();
    this->sonic->setY(y);
}

void Player::newLevel(float ancho_escenario){
	this->setX(100);
	this->setY(425);
	this->setAtEnd(false);
	this->sonic->setAnchoEscenario(ancho_escenario);
	int multiplicador = 10;
	if (this->monedas >= 50) multiplicador = 20;
	this->sumarPuntos(this->monedas*multiplicador);
	this->monedas = 0;
}

bool Player::llegoAlFinal(){
	return this->atEnd;
}

void Player::setAtEnd(bool end){
	this->atEnd = end;
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

float Player::getBordeDer(){

    return this->getX() + (this->collitionBoxes[this->getMovement()][0]);
}

float Player::getBordeIzq(){

    return this->getX();
}

float Player::getBordeArriba(){

    return this->getY();
}

float Player::getBordeAbajo(){

    return this->getY()  + (this->collitionBoxes[this->getMovement()][1]);
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
	vector<float> rodar;
    rodar.push_back(97);//MARTIN: CHEQUEAR ESTOS VALORES!
    rodar.push_back(121);//MARTIN: CHEQUEAR ESTOS VALORES!
    this->collitionBoxes[ROLLI] = rodar;
    this->collitionBoxes[ROLLD] = rodar;

	vector<float> daniar;
    daniar.push_back(97);//MARTIN: CHEQUEAR ESTOS VALORES!
    daniar.push_back(121);//MARTIN: CHEQUEAR ESTOS VALORES!
    this->collitionBoxes[DMGI] = daniar;
    this->collitionBoxes[DMGD] = daniar;
}

float Player::getCentroX(){
    return this->getX() + (this->collitionBoxes[this->getMovement()][0] / 2);
}

float Player::getCentroY(){
    return this->getY() + (this->collitionBoxes[this->getMovement()][1] / 2);
}

bool Player::enRangoX(Entidad* entidad){

    float bordeDerE = entidad->getBordeDer();
    float bordeIzqE = entidad->getBordeIzq();

    float bordeDerP = this->getBordeDer();
    float bordeIzqP = this->getBordeIzq();

    //return ( (bordeDerP == bordeIzqE) || (bordeDerE == bordeIzqP) );
	return !(bordeDerP < bordeIzqE || bordeDerE < bordeIzqP);//NO colisiona si bordeDer de personaje esta atras del bordeIzq de la entidad o bordeIzq de personaje esta mas adelante de bordeDer de entidad
}

bool Player::enRangoY(Entidad* entidad){

    float bordeArribaE = entidad ->getBordeArriba();
    float bordeAbajoE = entidad ->getBordeAbajo();

    float bordeArribaP = this->getBordeArriba();
    float bordeAbajoP = this->getBordeAbajo();

    //return ((bordeArribaE >= bordeAbajoP) || (bordeAbajoE <= bordeArribaP));
	return !(bordeAbajoP < bordeArribaE || bordeAbajoE < bordeArribaP);//TODO revisar orden correcto
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
    float bordeAbajoP = entidad -> getBordeAbajo();

    //agregar factores para retocar con mas presicion
    bool colisionX = ((bordeDerP > bordeIzqE) || (bordeDerE > bordeIzqP));
    bool contactoX = ((bordeDerP >= bordeIzqE) || (bordeDerE >= bordeIzqP));

    bool colisionY = ((bordeArribaP > bordeAbajoE) || (bordeArribaE < bordeAbajoP));
    bool contactoY = ((bordeArribaP >= bordeAbajoE) || (bordeArribaE <= bordeAbajoP));

    //CALCULO DE COLISIONES BASICAS CON 2 SPRITES RECTANGULARES.
    if (contactoX && contactoY){
        entidad->afectarA(this);
    }
    /*else if(colisionY && contactoX){
        entidad->afectarA(this);
    }*/
}

void Player::roll(){
	//this->sonic->roll();
	this->sonic->setRolling(true);
}

void Player::lastimar(){
	//this->sonic->lastimar();
	this->sonic->setDamaged(true);
}

void Player::caer(int dir){
	this->sonic->caer(dir);
}

void Player::setBaseY(float newy){
	this->sonic->setBaseY(newy);
}

out_message_t* Player::getStatus(float camPos){
    out_message_t* status = new out_message_t;
	memset(status, 0, sizeof(out_message_t));
    if(this->estaVivo()){
        status->ping = PLAYER_UPDATE;
        status->frame = this->getFrame();
    }
    else {
        status->ping = PLAYER_DEAD;
        status->frame = frameMuerto;
		frameSum++;
		if (frameSum%10 == 0){
			frameMuerto = frameSum / 10;
		}
    }
    status->id = atoi(this->getName().c_str());
    status->connection = this->isConnected();
    status->posX = this->getX();
    status->posY = this->getY();
    status->camPos = camPos;
    status->move = this->getMovement();

	status->rings = this->getMonedas();
	status->lives = this->getVidas();
	status->points = this->getIndivScore();
    switch(this->getEstado()){
        case PRUEBA:
            status->state = ESCUDO;break;
        case REVIVIENDO:
            status->state = ESCUDO;break;
        default:
            status->state = this->getEstado();break;
    }
    status->state_frame = this->estado->getFrame();
    if(this->puntaje->getNombre() == string("Equipo 2")){
        status->team = 2;
    }
    else{
        status->team = 1;
    }
    status->team_rings = this->puntaje->getMonedas();
    status->team_points = this->puntaje->getTotal();
    return status;
}

bool Player::mensajeDeMuertoEnviado(){
    return this->frameMuerto == 5;
}

bool Player::recibirGolpe(){

    if(this->estado->recibirGolpe()){
        if(!(this->getMonedas())){
            if(!(this->getVidas())){} // matar a sonic
            else this->quitarVida();
        }
        else this->quitarMonedas();
        return true;
    }
    return false;
}

int Player::getVidas(){
    return this->vidas;
}

int Player::getMonedas(){
    return this->monedas;
}

void Player::agregarMonedas(int n){
    this->puntaje->sumarMonedas(n);
    this->monedas += n;
}

void Player::quitarMonedas(){
    this->puntaje->sumarMonedas(-(this->monedas));
    this->monedas = 0;
}

void Player::quitarVida(){
    if(this->vidas > 1){
        this->vidas--;
        this->setEstado(REVIVIENDO);
    }
    else this->vivo = false;
}

bool Player::estaAtacando(){
    return ((this->sonic->estaRodando()) || (this->sonic->estaSaltando()));
}

bool Player::estaSaltando(){
    return this->sonic->estaSaltando();
}

bool Player::estaCayendo(){
    return this->sonic->estaCayendo();
}
void Player::sumarPuntos(int puntos){
    this->sumarIndivScore(puntos);
	this->puntaje->sumarPuntos(puntos);
}

long Player::getPuntos(){
	return this->puntaje->getParcial();
}

void Player::setIndivScore(int newscore){
	scoreIndiv = newscore;
}

int  Player::getIndivScore(){
	return scoreIndiv;
}
void Player::sumarIndivScore(int sc){
	scoreIndiv+=sc;
}

void Player::cambiarEquipo(Puntaje* newp){
	this->puntaje = newp;
}

void Player::setEstado(state_type estado){
    this->estado->set(estado);
}

void Player::setCayendo(){
    this->sonic->setCayendo();
}
bool Player::estaMirandoADer(){
	return this->sonic->estaMirandoADer();
}

state_type Player::getEstado(){
    return this->estado->get();
}
