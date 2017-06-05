#include "Control.hpp"
#include "../Modelo/Entidades/Piedra.hpp"
#include "../Modelo/Entidades/Pinche.hpp"
#include "../Modelo/Entidades/Moneda.hpp"
#include "../Modelo/Entidades/Cangrejo.hpp"
#include "../Modelo/Entidades/Pez.hpp"
#include "../Modelo/Entidades/Mosca.hpp"
#include "../Modelo/Entidades/Invencibilidad.hpp"
#include <stdio.h>
#include <sstream>

#define VELOCITY 0.35 //definidos como constantes pero lo mejor es pasarlos como parametro para que sea consistente con la vista
#define VEL -0.8
#define LVL1_END 4000
#define LVL2_END 5000
#define LVL3_END 6000

//int to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

Control::Control(gameMode game_mode){
	this->model = new Model(game_mode);
	this->cameraControl = new CameraControl(1200, LVL1_END); //el ancho de la camara tambien tiene que venir por parametro
    k = 0;
	//space_was_down=false;
}

void Control::addPlayer(string playerName){
	this->model->addPlayer(playerName);
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
	vector<float> directions = this->model->getPlayerDirections(playerName);
	float dirX = directions[0];
	float dirY = directions[1];
	move_type movement = this->model->getPlayerMovement(playerName);//TRY1

	switch( e ){
		//case QUIT: this->model->setPlayerConnection(playerName, false); break;
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
	return 	(this->cameraControl->moveCamera(newPlayerX,this->model,playerName,dirX));
}

bool Control::moveCameraAndPlayer(string playerName, vector<float> directions){
	vector<float> previousPlayerPosition = this->model->getPlayerPosition(playerName);
	this->model->movePlayer(playerName,directions[0],directions[1]);
	vector<float> newPlayerPosition = this->model->getPlayerPosition(playerName);
	float previousCameraPosition = this->getCameraPosition();
	if(!(this->moveCamera(newPlayerPosition[0],playerName,directions[0]))){
	 	//si no puedo mover la camara vuelvo a setear la posicion anterior del jugador
	 	this->model->setPlayerPosition(playerName,previousPlayerPosition[0]);
	 	return false;
	}
	if(this->getCameraPosition() != previousCameraPosition) this->model->moveDisconnectedPlayers(this->cameraControl->getLeftEdge(),this->cameraControl->getRightEdge(),directions[0]);
	return true;
}

void Control::setPlayerConnection(string playerName, bool connection){
	this->model->setPlayerConnection(playerName,connection);
}

vector<float> Control::getPlayerPosition(string playerName){
	return this->model->getPlayerPosition(playerName);
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
	move_type movement = this->model->getPlayerMovement(playerName);

	//obtengo las direcciones en base al key event
	vector<float> directions = this->getDirections(ev->key,SSTR(ev->id));

	//casos especiales, aca entran y debieran setear flag para que luego entren en update
	if(ev->key == DOWN_DOWN){
		this->model->playerRoll(playerName);
		return;
	}


	//muevo el jugador y la camara con las direcciones obtenidas
	this->model->movePlayer(playerName,directions[0], directions[1]);
}

void Control::update(){
	// en lugar de hacer los dos for llamar a:
	// this->model->colisionarTodos()  (afuera del for)
	vector<string> players = this->model->getPlayerNames();
	for(int i=0; i < players.size(); i++){

		vector<float> directions = this->model->getPlayerDirections(players[i]);
		this->moveCameraAndPlayer(players[i],directions);
	}
	this->model->moverEntidades();
    this->model->colisionarTodos();
}

vector<out_message_t*> Control::getStatus(){
	return this->model->getStatus(this->getCameraPosition());
}

void Control::crearEntidades(){
	Piedra* piedra = new Piedra(0,500, 345);
	this->model->addEntidad(piedra);
	Cangrejo* cangrejo = new Cangrejo(0,1000, 475);
	this->model->addEntidad(cangrejo);
    Pez* pez = new Pez(0, 800, 675);
	this->model->addEntidad(pez);
    Mosca* mosca = new Mosca(0,300, 225);
	this->model->addEntidad(mosca);
	Pinche* pinche = new Pinche(2, 1000, 495);
	this->model->addEntidad(pinche);
	Moneda* moneda1 = new Moneda(3, 550, 305);
	this->model->addEntidad(moneda1);
    Invencibilidad* bonus1 = new Invencibilidad(0, 750, 400);
    this->model->addEntidad(bonus1);
    /*
	Moneda* moneda2 = new Moneda(4,200,180);
	this->model->addEntidad(moneda2);
*/
}

vector<out_message_t*> Control::getEntidadesInitStatus(){
	return this->model->getEntidadesInitStatus();
}
