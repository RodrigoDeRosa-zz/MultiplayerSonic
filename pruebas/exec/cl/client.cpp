#include "client.hpp"
#include "socket.hpp"
#include "message.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <vector>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

Client::Client(const char* p, const char* h){
    socket = NULL;
    online = false;
    gameStarted = false;
    juego = NULL;
    pings = 0;
    port = p;
    hostname = h;
    received = deque<out_message_t*>();
    toSend = deque<key_event>();
}

Client::~Client(){
    if (socket) delete socket;
    socket = NULL;
    pings = 0;
    online = false;
    gameStarted = false;
}

void Client::addPlayer(){
	vector<float> player;
	player.push_back(0);
    player.push_back(0);
    player.push_back(100);
    player.push_back(300);
	player.push_back(1);
	players.push_back(player);
}

vector<float> Client::getPlayer(int index){
	return players[index];
}

void Client::updatePlayer(int index, float velX, float velY, float posX, float posY, float estado){
    vector<float> player;
	player = players[index];
	player[0] = velX;
	player[1] = velY;
	player[2] = posX;
	player[3] = posY;
	player[4] = estado;
    players[index] = player;
    printf("Nombre Jugador en Client: %d \n",index);
    printf("Posicion en Cliente despues de actualizar: x=%f y=%f \n",posX,posY);
}

void Client::updatePlayers(){
	for(int i = 0; i < (this->players).size(); i++){
		vector <float> player;
		player = players[i];

		float estado = player[4];

		this->juego->updateJugador(SSTR(i), player[0], player[1], player[2], player[3], estado);
	}
}

bool Client::setConnectionInfo(struct addrinfo *srvInfo){
    serverInfo = srvInfo;
    /*Se crea el socket del cliente*/
    socket = new Socket();
    if (!socket->sockInit()){
        return false;
    }
    return true;
}

bool Client::connectToServer(){
    if (!socket->sockConnect(serverInfo->ai_addr, serverInfo->ai_addrlen)){
        return false;
    }
    online = true;
    return true;
}

void Client::queueToSend(key_event event){
    toSend.push_back(event);
}

key_event Client::getEventToSend(){
    if (toSend.empty()){
        return KEY_TOTAL;
    }
    key_event element = toSend.at(0);
    toSend.pop_front();
    return element;
}

bool Client::send(void *buffer, int size){
    char* data = (char*) buffer;
    if(!socket->sockSend(data, size)){
        return false;
    }
    return true;
}

bool Client::receive(void *buffer, int size, long int dataLen){
    char* data = (char*) buffer;
    if (!socket->sockReceive(data, size, dataLen)){
        return false;
    }
    return true;
}

void Client::queueReceived(out_message_t* state){
    received.push_back(state);
}

out_message_t* Client::getEventReceived(){
    if (received.empty()) return NULL;
    out_message_t* element = received.at(0);
    received.pop_front();
    return element;
}

bool Client::connected(){
    return online;
}

bool Client::gameOn(){
    return gameStarted;
}

void Client::startGame(){
    gameStarted = true;
}

void Client::endGame(){
    gameStarted = false;
}

Juego* Client::getJuego(){
    return this->juego;
}

void Client::addJuego(Juego* j){
    juego = j;
}

void Client::disconnect(int how){
    if (how == 1 && online) printf("Lost connection with server. Disconnecting...\n");
    socket->sockShutdown(SHUT_RDWR);
    socket->sockClose();
    online = false;
    gameStarted = false;
    pings = 0;
}
