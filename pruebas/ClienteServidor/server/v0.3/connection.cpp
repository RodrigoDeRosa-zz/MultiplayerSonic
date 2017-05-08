#include "connection.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include <pthread.h>
#include <deque>
#include <string.h>
#include <stdio.h>
using namespace std;

#define MAX_DATASIZE 200

void* read(void* arg){
    Connection* connection = (Connection*) arg;
    char message[MAX_DATASIZE];
	char msg_buffer[MAX_DATASIZE];

    while (connection->isOnline()){
        /*Si falla la recepcion se considera que se perdio la conexion*/
        if(!connection->receiveMessage(msg_buffer, MAX_DATASIZE)){
            connection->disconnect();
            break;
        }
		strcpy(message,msg_buffer);
        if (!strcmp(message, "")) continue;
		if (!strcmp(strtok(message, "\n"), "ping")) continue;
        printf("message: %s\n", message);
        CXManager::getInstance().queueInEvent(message);
    }

    return NULL;
}

void* write(void* arg){
    Connection* connection = (Connection*) arg;
    char* message;

    while (connection->isOnline()){
        /*Toma el mensaje de la cola de eventos salientes*/
        message = connection->getOutEvent();
        if (!message) continue; //Si esta vacia la cola, sigue
        /*Si no se puede enviar el mensaje se considera que la conexion esta caida*/
        if(!connection->sendMessage(message, strlen(message))) connection->disconnect();
    }

    return NULL;
}

Connection::Connection(Socket* sock){
    socket = sock;
    online = true;
    /*Se crean los threads de recepcion y envio de la conexion*/
    pthread_create(&reader, NULL, read, this);
    pthread_create(&writer, NULL, write, this);
}

Connection::~Connection(){

}

void Connection::disconnect(){
    online = false;
    CXManager::getInstance().removeConnection(id);
    if (socket){
        socket->sockClose();
        socket = NULL;
    }
    void* exit_status;
    pthread_join(reader, &exit_status);
    pthread_join(writer, &exit_status);
}

void Connection::setID(int n){
    id = n;
}

bool Connection::isOnline(){
    return online;
}

bool Connection::receiveMessage(char* buffer, int size){
    if(!socket->sockReceive(buffer, size)) return false;
    return true;
}

bool Connection::sendMessage(char* buffer, int size){
    if(!socket->sockSend(buffer, size)) return false;
    return true;
}

void Connection::queueOutEvent(char* event){
    outEvents.push_back(event);
}

char* Connection::getOutEvent(){
    if (outEvents.empty()) return NULL;
    char* event = outEvents.at(0);
    outEvents.pop_front();
    return event;
}
