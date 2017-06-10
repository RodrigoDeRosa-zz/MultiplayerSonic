#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include "../../../message.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

#define BACKLOG 10

#define USLEEP_EVENTHANDLING 1000	//[useg]
void* eventHandling(void* arg){
    /*Mientras el servidor esta conectado, busca eventos para procesar*/
    while(Server::getInstance().isOnline()){
        /*  Cuando lo encola, se lo da al juego para que lo procese y el se encarga
         *de encolar el evento saliente en outEvent.
         *  Como el juego puede tardar, se sigue ciclando viendo si llegaron eventos
         *a inEvents o a outEvents hasta que en alguno de los dos haya algo.
         *  Cuando el juego devuelve un outEvent, se lo envia al connection manager
         *para que se lo pase a todas sus conexiones.
        */
        char* outEvent = Server::getInstance().getOutEvent();
        if (outEvent) CXManager::getInstance().queueOutEvent(outEvent);
		else usleep(USLEEP_EVENTHANDLING);
    }

    return NULL;
}

Server::Server(){
    serverInfo = NULL;
    accSocket = NULL;
    online = false;
    initialize = false;
	pthread_mutex_init(&inEventsMux,NULL);
	pthread_mutex_init(&outEventsMux,NULL);
}

Server::~Server(){
    serverInfo = NULL;
	pthread_mutex_destroy(&inEventsMux);
	pthread_mutex_destroy(&outEventsMux);
    disconnect();
}

/*Setea la informacion del servidor*/
bool Server::setInfo(const char* port){
    struct addrinfo hints;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, port, &hints, &serverInfo);
    if (status != 0) return false;

    return true;
}

Server& Server::getInstance(){
    static Server instance;
    return instance;
}

bool Server::init(const char* port){
    /*Se configura la informacion del servidor*/
    if (!this->setInfo(port)) return false;
    /*Se crea el socket de aceptacion*/
    accSocket = new Socket();
    if (!accSocket->sockInit()){
        delete accSocket;
        accSocket = NULL;
        return false;
    }
    return true;
}

bool Server::setOnline(){
    bool status;
    /*Bind a la direccion del server*/
    status = accSocket->sockBind(serverInfo->ai_addr, serverInfo->ai_addrlen);
    if (!status) return false;
    /*Se pasiva el socket para escuchar.*/
    status = accSocket->sockListen(BACKLOG);
    /*Si pudo pasivar al socket, inicia un thread donde maneja los eventos.*/
    if(status){
        online = true;
        pthread_create(&eventThread, NULL, eventHandling, NULL);
    }
    return status;
}

Socket* Server::accept(){
    struct addrinfo clientAddr;
    Socket* newSock = accSocket->sockAccept(clientAddr.ai_addr, &(clientAddr.ai_addrlen));
    //Aca se podria imprimir la direccion de donde se acepto la conexion. (en el logger)
    return newSock;
}

bool Server::isOnline(){
    return online;
}

void Server::disconnect(){
    if (accSocket){
        accSocket->sockClose();
        accSocket = NULL;
    }
    /*Cierra el thread de manejo de eventos*/
    pthread_cancel(eventThread);
    online = false;
}

void Server::queueInEvent(in_message_t* event){
	pthread_mutex_lock(&inEventsMux);
    inEvents.push_back(event);
	pthread_mutex_unlock(&inEventsMux);
}

void Server::queueOutEvent(char* event){
	pthread_mutex_lock(&outEventsMux);
	outEvents.push_back(event);
	pthread_mutex_unlock(&outEventsMux);
}

char* Server::getOutEvent(){
	pthread_mutex_lock(&outEventsMux);
    if (outEvents.empty()) {
		pthread_mutex_unlock(&outEventsMux);
		return NULL;
    }
    char* event = outEvents.at(0);
    outEvents.pop_front();
	pthread_mutex_unlock(&outEventsMux);
    return event;
}

in_message_t* Server::getInEvent(){
	pthread_mutex_lock(&inEventsMux);
    if (inEvents.empty()) {
		pthread_mutex_unlock(&inEventsMux);
		return NULL;
    }
    in_message_t* event = inEvents.at(0);
    inEvents.pop_front();
	pthread_mutex_unlock(&inEventsMux);
    return event;
}

void Server::startInitializing(){
    initialize = true;
}

bool Server::initializing(){
    return initialize;
}

bool Server::is_running(){
	return game_is_on;
}

void Server::start_game(){
	game_is_on=true;
}

void Server::end_game(){
	game_is_on=false;
}
