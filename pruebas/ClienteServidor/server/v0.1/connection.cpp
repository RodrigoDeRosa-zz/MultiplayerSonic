#include "cxManager.hpp"
#include "socket.hpp"
#include "server.hpp"
#include <string>
#include <pthread.h>
using namespace std;

#define MAXDATASIZE 100

void* receive(void* arg){
    Connection* self = (Connection*) arg;

    int rv;
    while (self->status == ALIVE || self->status == NEWBORN){
        char message[MAXDATASIZE];
        rv = self->socket->sockReceive(message, MAXDATASIZE);
        if (!rv) self->status = CLOSED;
        self->server->queueEvent(message);
    }

    return NULL;
}

void* send(void* arg){
    Connection* self = (Connection*) arg;

    while(self->status == ALIVE || self->status == NEWBORN){
        char* message = self->();
        if (!message) continue;
        /*Bloquea y envia*/
        pthread_mutex_lock(&socketLock);
        bool status = client->send(message, strlen(message));
        pthread_mutex_unlock(&socketLock);
        if (!status){
            client->disconnect(1);
        }
    }
    return NULL;
}

Connection::Connection(Socket* skt, Server* sv){
    socket = skt;
    server = sv;
    status = NEWBORN;

    username = "";

    pthread_create(&reader, NULL, receive, this);
    pthread_create(&writer, NULL, send, this);
}

Connection::~Connection(){
    if (socket) delete socket;
    socket = NULL;
    username = "";
}

Connection::join(){
    void* exit_status;
    pthread_join(reader, &exit_status);
    pthread_join(writer, &exit_status);
}

string Connection::getUsername(){
    return username;
}

void Connection::setUsername(string user){
    username = user;
    status = ALIVE;
}
