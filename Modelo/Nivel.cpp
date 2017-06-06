#include "Nivel.hpp"
#include <stdio.h>

Nivel::Nivel(gameMode game_mode){
	players = new vector<Player*>();
	entidades = new vector<Entidad*>();
	puntajes = new vector<Puntaje*>();
	this->playerStatusControl = 0;
	this->entidadesStatusControl = 0;
	this->modo_juego = game_mode;
	termino = false;
	es_transicion = false;

	vector<string>* nombresPuntajes	= new vector<string>();
	int cant_puntajes = 0;
	switch(this->modo_juego){
		case INDIVIDUAL:
			cant_puntajes = 4;
			nombresPuntajes->push_back(string("Jugador 1"));
			nombresPuntajes->push_back(string("Jugador 2"));
			nombresPuntajes->push_back(string("Jugador 3"));
			nombresPuntajes->push_back(string("Jugador 4"));
			break;
		case COOP:
			cant_puntajes = 1;
			nombresPuntajes->push_back(string("Jugadores"));
			break;
		case EQUIPOS:
			cant_puntajes = 2;
			nombresPuntajes->push_back(string("Equipo 1"));
			nombresPuntajes->push_back(string("Equipo 2"));
			break;	
	}
	for (int i = 0; i < cant_puntajes; i++){
		Puntaje* p = new Puntaje(nombresPuntajes->at(i));
		puntajes->push_back(p);
	}
}

void Nivel::addPlayer(string playerName){
	Puntaje* p;
	switch(this->modo_juego){
		case INDIVIDUAL:
			p = puntajes->at(players->size());break;
		case COOP:
			p = puntajes->front();break;
		case EQUIPOS:
			if (players->size() < 2){	//si es el primer o segundo jugador
				p = puntajes->front();
			}
			else{						//sino es el tercer o cuarto
				p = puntajes->back();
			}
			break;
	}
	Player* player = new Player(playerName, p);
	//TODO CAMBIAR CONSTRUCTOR DE PLAYER PARA QUE RECIBA PUNTAJE
	(this->players)->push_back(player);
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

void Nivel::setPlayerConnection(string playerName, bool connection){
	Player* player = this->getPlayer(playerName);
	player->setConnected(connection);
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
	for (int i = 0; i < (players)->size(); i++) {
		for (int j = 0; j < (entidades)->size(); j++) {

			if ((*entidades)[j]->estaDestruida()) continue;

			if ((*players)[i]->enRangoX((*entidades)[j])) {
				if ((*players)[i]->enRangoY((*entidades)[j])) {
					(*players)[i]->afectarseCon((*entidades)[j]);
				}
			}

			if ((*players)[i]->enRangoY((*entidades)[j])) {
				if ((*players)[i]->enRangoX((*entidades)[j])) {
					(*players)[i]->afectarseCon((*entidades)[j]);
				}
			}
		}
	}
}

void Nivel::playerRoll(string playerName){
	Player* player = this->getPlayer(playerName);
	player->roll();
}

vector<out_message_t*> Nivel::getPlayerStatus(float camPos){
	vector<out_message_t*> v;
	for(int i=0; i < (this->players)->size(); i++){
		if (this->playerStatusControl < 10){
            this->playerStatusControl++;
            continue;
        }
        this->playerStatusControl = 0;
		v.push_back((*(this->players))[i]->getStatus(camPos));
	}
	return v;
}

vector<out_message_t*> Nivel::getEntidadesStatus(){
	vector<out_message_t*> v;
	for(int i=0; i < (this->entidades)->size(); i++){
		if (this->entidadesStatusControl < 10){
            this->entidadesStatusControl++;
            continue;
        }
        this->entidadesStatusControl = 0;
		v.push_back((*(this->entidades))[i]->getOutMessage());
		if((*(this->entidades))[i]->estaDestruida()) {
			// una vez que se mando el mensaje de que esta destruida, se borra la entidad
			this->entidades->erase(this->entidades->begin() + i);
		}
	}
	return v;
}


vector<out_message_t*> Nivel::getStatus(float camPos){
	vector<out_message_t*> playerVector = this->getPlayerStatus(camPos);
	vector<out_message_t*> entidadesVector = this->getEntidadesStatus();
	playerVector.insert(playerVector.end(),entidadesVector.begin(),entidadesVector.end());
	return playerVector;
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

bool Nivel::esTransicion(){
	return es_transicion;
}

bool Nivel::yaTermino(){
	return termino;
}
