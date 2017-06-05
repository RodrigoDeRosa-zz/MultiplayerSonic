#include "client.hpp"
#include "socket.hpp"
#include "../../../message.hpp"
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
	out_message_t* player = new out_message_t;
    player->posX = 100;
    player->posY = 300;
    player->move = IDLED;
    player->frame = 0;
	player->connection = true;
    player->rings = 0;
    player->lives = 0;
    player->points = 0;
	players.push_back(player);
}

void Client::cleanPlayers(){
    players.clear();
}

out_message_t* Client::getPlayer(int id){
	return players[id];
}

void Client::updatePlayer(out_message_t* message){
    out_message_t* player = players[message->id];
    player->posX = message->posX;
    player->posY = message->posY;
    player->move = message->move;
    player->frame = message->frame;
    player->connection = message->connection;
    player->rings = message->rings;
    player->lives = message->lives;
    player->points = message->points;
    player->state = message->state;
    player->state_frame = message->state_frame;
    players[message->id] = player;
}

void Client::updatePlayers(){
	for(int i = 0; i < (this->players).size(); i++){
		out_message_t* player = players[i];

		this->juego->updateJugador(SSTR(i), player->posX, player->posY, player->move, player->frame, player->connection,
            player->rings, player->lives, player->points, player->state, player->state_frame);
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
    endGame();
    if (how == 1 && online) printf("Lost connection with server. Disconnecting...\n"); //NO LOGGEAR
    socket->sockShutdown(SHUT_RDWR);
    socket->sockClose();
    online = false;
    pings = 0;
}
