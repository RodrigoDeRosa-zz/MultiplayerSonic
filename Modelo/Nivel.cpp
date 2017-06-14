#include "Nivel.hpp"
#include <stdio.h>

Nivel::Nivel(float end){

	/*Vectores inicializados*/
	players = new vector<Player*>();
	entidades = new vector<Entidad*>();
	puntajes = new vector<Puntaje*>();

	/*Variables que ni idea*/
	this->playerStatusControl = 0;
	this->entidadesStatusControl = 0;

	termino = false;
	changeLevelMessageSent = false;
	this->end = end;
}

float Nivel::getEnd(){
	return this->end;
}

void Nivel::terminar(){
	bool jugadores_en_final = true;
	for(int i = 0; i < players->size(); i++){
		if (!(*players)[i]->isConnected()){
			jugadores_en_final = jugadores_en_final;
			continue;
		}
		jugadores_en_final = jugadores_en_final && (*players)[i]->llegoAlFinal();
	}
	if(jugadores_en_final) this->termino = true;
}

void Nivel::addPlayers( vector<Player*>* vec){
	this->players = vec;
}

void Nivel::addPuntajes( vector<Puntaje*>* vec){
	this->puntajes = vec;
}

void Nivel::start(){
	for(int i = 0; i < players->size(); i++){
		(*players)[i]->newLevel(this->end);
	}
}

void Nivel::setPrueba(string playerName){
	Player* player = this->getPlayer(playerName);
	if(player->getEstado() == PRUEBA) player->setEstado(NORMAL);
	else player->setEstado(PRUEBA);
}

void Nivel::addEntidades( vector<Entidad*>* vec){
	this->entidades = vec;
}

void Nivel::addEntidad(Entidad* entidad){
	(this->entidades)->push_back(entidad);
}

Player* Nivel::getPlayer(string nombre){
	for(int i = 0; i < players->size(); i++){
		if(((*players)[i])->getName() == nombre){
			return (*players)[i];
		}
	}
	return NULL;
}

void Nivel::setPlayerPosition(string playerName, float x){
	Player* player = this->getPlayer(playerName);
	player->setX(x);
}

void Nivel::movePlayer(string playerName, float dirX, float dirY){
	Player* player = this->getPlayer(playerName);
	player->updateXY(dirX,dirY);
	if(player->getBordeDer() >= this->end-120) player->setAtEnd(true);
}

vector<float> Nivel::getPlayerPosition(string playerName){
	vector<float> position;
	Player* player = this->getPlayer(playerName);
	position.push_back(player->getX());
	position.push_back(player->getY());
	return position;
}

vector<float> Nivel::getPlayerDirections(string playerName){
	vector<float> directions;
	Player* player = this->getPlayer(playerName);
	directions.push_back(player->getDirX());
	directions.push_back(player->getDirY());
	return directions;
}

bool Nivel::otherPlayerInPosition(string playerName,float position, bool left){
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

void Nivel::moveDisconnectedPlayers(float cameraLeftEdge,float cameraRightEdge,float dirX){
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

void Nivel::setPlayerConnection(string playerName, bool connection) {
	Player *player = this->getPlayer(playerName);
	if (player) {
		player->setConnected(connection);
	}
}
vector<string> Nivel::getDisconnectedPlayers(){
	vector<string> names;
	for(int i = 0; i < players->size(); i++){
		if(!((*players)[i]->isConnected())) names.push_back((*players)[i]->getName());
	}
	return names;
}

move_type Nivel::getPlayerMovement(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->getMovement();
}

int Nivel::getPlayerFrame(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->getFrame();
}

vector<string> Nivel::getPlayerNames(){
	vector<string> v;
	for(int i = 0; i < this->players->size(); i++){
		v.push_back((*(this->players))[i]->getName());
	}
	return v;
}

bool Nivel::playerIsConnected(string playerName){
	Player* player = this->getPlayer(playerName);
	return player->isConnected();
}

bool Nivel::enRango(Entidad* entidad, Player* player){

	float bordeDerE = entidad->getBordeDer();
	float bordeIzqE = entidad->getBordeIzq();

	float bordeDerP = player->getBordeDer();
	float bordeIzqP = player->getBordeIzq();

	return ((bordeDerP == bordeIzqE) || (bordeDerE == bordeIzqP));
}

void Nivel::colisionarTodos() {

	bool colisionoPiedra = false;

	for (int i = 0; i < (players)->size(); i++) {
		if((!((*(players))[i]->estaVivo())) || (!((*(players))[i]->isConnected())) ) continue;
		for (int j = 0; j < (entidades)->size(); j++) {

			if ((*entidades)[j]->estaDestruida()) continue;

			else if ((*players)[i]->enRangoX((*entidades)[j])) {
				if ((*players)[i]->enRangoY((*entidades)[j])) {
					if(((*entidades)[j])->esPiedra()){
						 colisionoPiedra = true;
					}
					(*players)[i]->afectarseCon((*entidades)[j]);
				}
			}

			else if ((*players)[i]->enRangoY((*entidades)[j])) {
				if ((*players)[i]->enRangoX((*entidades)[j])) {

					if(((*entidades)[j])->esPiedra()){
						colisionoPiedra = true;
					}
					(*players)[i]->afectarseCon((*entidades)[j]);
				}
			}
		}
		/*
        if (!colisionoPiedra && !(*players)[i]->estaSaltando() && (*players)[i]->getY() >= 345  && (*players)[i]->getY() < 425 ){
            //(*players)[i]->caer(0);
        //colisionoPiedra = false;
        }
		*/
		if(!colisionoPiedra){
			(*players)[i]->setBaseY(425);
			if ((!(*players)[i]->estaSaltando()) && (*players)[i]->getY() < 425){
				(*players)[i]->setCayendo();
			}
		}
		colisionoPiedra = false;
	}
}

void Nivel::playerRoll(string playerName){
	Player* player = this->getPlayer(playerName);
	player->roll();
}

vector<out_message_t*> Nivel::getPlayerStatus(float camPos){
	vector<out_message_t*> v;
	for(int i=0; i < (this->players)->size(); i++){
		/*if (this->playerStatusControl < 10){
            this->playerStatusControl++;
            continue;
        }
        this->playerStatusControl = 0;*/
		
		if(!((*(this->players))[i]->estaVivo()) && ((*(this->players))[i]->mensajeDeMuertoEnviado())) {
			this->players->erase(this->players->begin() + i);
		}
		v.push_back((*(this->players))[i]->getStatus(camPos));
	}
	return v;
}

vector<out_message_t*> Nivel::getEntidadesStatus(){
	vector<out_message_t*> v;
	for(int i=0; i < (this->entidades)->size(); i++){
		/*if (this->entidadesStatusControl < 10){
            this->entidadesStatusControl++;
            continue;
        }
        this->entidadesStatusControl = 0;*/
		v.push_back((*(this->entidades))[i]->getOutMessage());
		if((*(this->entidades))[i]->estaDestruida()) {
			// una vez que se mando el mensaje de que esta destruida, se borra la entidad
			this->entidades->erase(this->entidades->begin() + i);
		}
	}
	return v;
}

vector<out_message_t*> Nivel::getStatus(float camPos){
	vector<out_message_t*> v;
	if(!(this->changeLevelMessageSent)){
		out_message_t* state = new out_message_t;
		state->ping = CHANGE_LEVEL;
		state->id = 0;
		state->connection = true;
		state->posX = 0;
		state->posY = 0;
		state->camPos = 0;
		state->move = MOVE_TOTAL;
		state->frame = 0;
		state->rings = 0;
		state->lives = 0;
		state->points = 0;
		state->state = NORMAL;
		state->state_frame = 0;
		this->changeLevelMessageSent = true;
		v.push_back(state);
	}
	vector<out_message_t*> playerVector = this->getPlayerStatus(camPos);
	v.insert(v.end(),playerVector.begin(),playerVector.end());
	vector<out_message_t*> entidadesVector = this->getEntidadesStatus();
	v.insert(v.end(),entidadesVector.begin(),entidadesVector.end());
	return v;
}

void Nivel::moverEntidades(){
	for(int i = 0; i < this->entidades->size(); i++){
		(*(this->entidades))[i]->mover();
	}
}

vector<out_message_t*> Nivel::getEntidadesInitStatus(){
	vector<out_message_t*> v;
	for(int i=0; i < (this->entidades)->size(); i++){
		v.push_back((*(this->entidades))[i]->getInitMessage());
	}
	return v;
}

bool Nivel::yaTermino(){
	return termino;
}
