
#include "Control.hpp"
#include "Ubicador.hpp"
#include "../Modelo/Entidades/Piedras/Piedra.hpp"
#include "../Modelo/Entidades/Pinche.hpp"
#include "../Modelo/Entidades/Moneda.hpp"
#include "../Modelo/Entidades/Cangrejo.hpp"
#include "../Modelo/Entidades/Pez.hpp"
#include "../Modelo/Entidades/Mosca.hpp"
#include "../Modelo/Entidades/Invencibilidad.hpp"
#include "../Modelo/Entidades/Plataforma.hpp"
#include "../Modelo/Entidades/BonusMoneda.hpp"
#include "../Modelo/Entidades/Escudo.hpp"
#include "../Modelo/Entidades/Jefe.hpp"
#include "../Modelo/Entidades/Bola.hpp"
#include <stdio.h>
#include <sstream>

#define VELOCITY 0.35 //definidos como constantes pero lo mejor es pasarlos como parametro para que sea consistente con la vista
#define VEL -0.8
#define LVL1_END 4000
#define LVL2_END 5000
#define LVL3_END 6000

//defines para asegurar minimos y maximos (puede que este más acotado)
#define MIN_COINS	50	//por ejemplo esto asegura que nunca se va a generar un nivel en el que haya menos de MIN_COINS monedas, no importa el parametro que se pase
#define MAX_COINS	100	//y este dice que si le pasas 120 como max_coins igual el maximo es 100

#define MIN_CRABS	0
#define MAX_CRABS	15

#define MIN_FISHES	0
#define MAX_FISHES	20

#define MIN_FLIES	0
#define MAX_FLIES 	10

#define MIN_SPIKES	0
#define MAX_SPIKES	5

#define MIN_ROCKS	0
#define MAX_ROCKS	10

#define MIN_BONUSES	0
#define MAX_BONUSES	6

#define NIVEL1 0
#define NIVEL2 2
#define NIVEL3 4

//int to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

Control::Control(gameMode game_mode){
	this->modelo = new Modelo(game_mode);
	this->cameraControl = new CameraControl(1200, LVL1_END); //el ancho de la camara tambien tiene que venir por parametro
    k = 0;
	this->initNiveles();
	this-> nivelActual = 0;
	this->terminado = false;
}

gameMode Control::getGameMode(){
	return this->modelo->getGameMode();
}

void Control::initNiveles(){
	/*Aca se deberian terminar de inicializa los niveles,
	 * y si es necesario las pantallas de transicion.*/

	Nivel* nivel1 = new Nivel(LVL1_END/*,true*/);
	this->niveles.push_back(nivel1);

	Transicion* transicion1 = new Transicion();
	this->niveles.push_back(transicion1);

    Nivel* nivel2 = new Nivel(LVL2_END);
    this->niveles.push_back(nivel2);

    Transicion* transicion2 = new Transicion();
	this->niveles.push_back(transicion2);

    Nivel* nivel3 = new Nivel(LVL3_END, true);
    this->niveles.push_back(nivel3);

    Transicion* transicion3 = new Transicion();
	this->niveles.push_back(transicion3);
}

void Control::addPlayer(string playerName, int equipo){

	this->modelo->createPersonaje(playerName,equipo);

    vector<Player*>* vec = this->modelo->getPersonajes();
    vector<Puntaje*>* vec2 = this->modelo->getPuntajes();

    this->getNivelActual()->addPlayers( vec );
    this->getNivelActual()->addPuntajes( vec2 );
}

float Control::getCameraPosition(){
	return this->cameraControl->getPosition();
}

vector<float> Control::getDirections(SDL_Event e, float dirX, float dirY){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch( e.key.keysym.sym ){
			case SDLK_SPACE: dirY -= 1; break;
			case SDLK_LEFT: dirX -= 1; break;
			case SDLK_RIGHT: dirX += 1; break;
		}
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0){
		switch( e.key.keysym.sym ){
			case SDLK_SPACE: dirY += 1; break;
			case SDLK_LEFT: dirX += 1; break;
			case SDLK_RIGHT: dirX -= 1; break;
		}
	}
	vector<float> directions;
	directions.push_back(dirX);
	directions.push_back(dirY);
	return directions;
}

vector<float> Control::getDirections(key_event e, string playerName){
	vector<float> directions = this->getNivelActual()->getPlayerDirections(playerName);
	float dirX = directions[0];
	float dirY = directions[1];
	move_type movement = this->getNivelActual()->getPlayerMovement(playerName);//TRY1

	switch( e ){
		//case QUIT: this->getNivelActual()->setPlayerConnection(playerName, false); break;
		case SPACE_DOWN: dirY -= 1; break;
		case LEFT_DOWN: dirX -= 1; break;
		case RIGHT_DOWN: dirX += 1; break;
		case SPACE_UP: dirY += 1; break;
		case LEFT_UP:  if (dirX) dirX += 1; break;
		case RIGHT_UP: if (dirX) dirX -= 1; break;
	}
	directions[0] = dirX;
	directions[1] = dirY;
	return directions;
}

bool Control::moveCamera(float newPlayerX,string playerName,float dirX){
	return 	(this->cameraControl->moveCamera(newPlayerX,this->getNivelActual(),playerName,dirX));
}

bool Control::moveCameraAndPlayer(string playerName, vector<float> directions){
	vector<float> previousPlayerPosition = this->getNivelActual()->getPlayerPosition(playerName);
	this->getNivelActual()->movePlayer(playerName,directions[0],directions[1]);
	vector<float> newPlayerPosition = this->getNivelActual()->getPlayerPosition(playerName);
	float previousCameraPosition = this->getCameraPosition();
	if(!(this->moveCamera(newPlayerPosition[0],playerName,directions[0]))){
	 	//si no puedo mover la camara vuelvo a setear la posicion anterior del jugador
	 	this->getNivelActual()->setPlayerPosition(playerName,previousPlayerPosition[0]);
	 	return false;
	}
	if(this->getCameraPosition() != previousCameraPosition) this->getNivelActual()->moveDisconnectedPlayers(this->cameraControl->getLeftEdge(),this->cameraControl->getRightEdge(),directions[0]);
	return true;
}

void Control::setPlayerConnection(string playerName, bool connection){
	this->getNivelActual()->setPlayerConnection(playerName,connection);
}

vector<float> Control::getPlayerPosition(string playerName){
	return this->getNivelActual()->getPlayerPosition(playerName);
}

void setOutMessage(out_message_t* message, message_type ping,int id,bool connection,int frame,move_type move,float posX,float posY,float camPos){
	message->ping = ping;
	message->id = id;
	message->connection = connection;
	message->posX = posX;
	message->posY = posY;
	message->frame = frame;
	message->move = move;
	message->camPos = camPos;
}

void Control::handleInMessage(in_message_t* ev){
	string playerName = SSTR(ev->id);
	move_type movement = this->getNivelActual()->getPlayerMovement(playerName);

	//obtengo las direcciones en base al key event
	vector<float> directions = this->getDirections(ev->key,SSTR(ev->id));

	//casos especiales, aca entran y debieran setear flag para que luego entren en update
	if(ev->key == DOWN_DOWN){
		this->getNivelActual()->playerRoll(playerName);
		//return;
	}

	if(ev->key == UP_DOWN){
		this->getNivelActual()->setPrueba(playerName);
		//return;
	}

	//muevo el jugador y la camara con las direcciones obtenidas
	this->getNivelActual()->movePlayer(playerName,directions[0], directions[1]);
}

bool Control::terminoElJuego(){
	return this->terminado;
}

void Control::update(){
    if (this->nivelActual == this->niveles.size()) return;
	if(this->getNivelActual()->yaTermino()){
		this->nivelActual++;
		if(this->nivelActual == this->niveles.size()){
			this->terminado = true;
            return;
		}
        this->cameraControl->reset(this->getNivelActual()->getEnd());
		this->getNivelActual()->addPlayers(this->modelo->getPersonajes());
		this->getNivelActual()->addPuntajes(this->modelo->getPuntajes());
        this->getNivelActual()->start();
	}
	vector<string> players = this->getNivelActual()->getPlayerNames();
    for(int i=0; i < players.size(); i++){
        vector<float> directions = this->getNivelActual()->getPlayerDirections(players[i]);
        this->moveCameraAndPlayer(players[i],directions);
    }
    this->getNivelActual()->moverEntidades();
    this->getNivelActual()->colisionarTodos();
    this->getNivelActual()->terminar();
}

vector<out_message_t*> Control::getStatus(){
	return this->getNivelActual()->getStatus(this->getCameraPosition());
}

void Control::cambiarEquipo(string playerName, int equipo){
	this->modelo->cambiarEquipo(playerName, equipo);
}

Entidad* obtenerEntidad(terna_t* terna){
	switch(terna->tipo){
		case COIN:
			return new Moneda(terna->id,terna->x,terna->y);
		case CRAB:
			return new Cangrejo(terna->id,terna->x,terna->y);
		case FLY:
			return new Mosca(terna->id,terna->x,terna->y);
		case FISH:
			return new Pez(terna->id,terna->x,terna->y);
		case SPIKE:
			return new Pinche(terna->id,terna->x,terna->y);
		case ROCK:
			return new Piedra(terna->id,terna->x,terna->y);
		case BONUS:
			int type = (terna->id)%3;
			switch(type){
				case 0:
					return new BonusMoneda(terna->id,terna->x,terna->y);
				case 1:
					return new Invencibilidad(terna->id,terna->x,terna->y);
				case 2:
					return new Escudo(terna->id,terna->x,terna->y);
			}
	}
}

vector<int> obtenerParametros(Json::Value json){
	vector<int> v;
	v.push_back(json["monedas"]["min"].asInt());
	v.push_back(json["monedas"]["max"].asInt());
	v.push_back(json["cangrejos"]["min"].asInt());
	v.push_back(json["cangrejos"]["max"].asInt());
	v.push_back(json["moscas"]["min"].asInt());
	v.push_back(json["moscas"]["max"].asInt());
	v.push_back(json["peces"]["min"].asInt());
	v.push_back(json["peces"]["max"].asInt());
	v.push_back(json["pinches"]["min"].asInt());
	v.push_back(json["pinches"]["max"].asInt());
	v.push_back(json["piedras"]["min"].asInt());
	v.push_back(json["piedras"]["max"].asInt());
	v.push_back(json["bonus"]["min"].asInt());
	v.push_back(json["bonus"]["max"].asInt());
	return v;
}

void Control::crearEntidades(string nombreNivel ,Json::Value json, int i){
	Ubicador* ubicador = new Ubicador();

	vector<int> parametros = obtenerParametros(json["entidades"][nombreNivel]);
	ubicador->setParams(parametros[0],parametros[1],parametros[2],parametros[3],parametros[4],parametros[5],parametros[6],parametros[7],parametros[8],parametros[9],parametros[10],
						parametros[11],parametros[12],parametros[13]);
	vector<terna_t*>* ternas = ubicador->generarTernas(this->niveles[i]->getEnd());
	for(int j=0; j < ternas->size(); j++){
		this->niveles[i]->addEntidad(obtenerEntidad((*ternas)[j]));
	}
}

void Control::crearEntidades(Json::Value json){
	//crearEntidades("nivel1",json,0);
	//crearEntidades("nivel1",json,2);
	//crearEntidades("nivel1",json,4);
// NIVEL_JEFE_ORIG es 4
// NIVEL_JEFE_TEST es 0

    //Pinche* pinche = new Pinche(0, 500, 500);
    //this->niveles[NIVEL1]->addEntidad(pinche);

	Jefe* jefe = new Jefe(0,5500,50);
	Bola* bola = new Bola(0,5500,120,jefe);
	this->niveles[NIVEL3]->addEntidad(jefe);
	this->niveles[NIVEL3]->addEntidad(bola);

    Plataforma* platform1 = new Plataforma(0, 500, 345);
    this->niveles[NIVEL1]->addEntidad(platform1);
}

vector<out_message_t*> Control::getEntidadesInitStatus(){
	vector<out_message_t*> v;
	for(int i = 0; i < this->niveles.size(); i++){
		vector<out_message_t*> entidades_v = this->niveles[i]->getEntidadesInitStatus();
		for(int j = 0; j < entidades_v.size(); j++){
            switch (i) {
                case NIVEL1:
                    entidades_v[j]->state_frame = 1; break;
                case NIVEL2:
                    entidades_v[j]->state_frame = 3; break;
                case NIVEL3:
                    entidades_v[j]->state_frame = 5; break;
            }
		}
		v.insert(v.end(),entidades_v.begin(),entidades_v.end());
	}
	return v;
}

Nivel* Control::getNivelActual(){
	return this->niveles[this->nivelActual];
}

int Control::getLevelNum(){
    return nivelActual;
}
