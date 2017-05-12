#include "client.hpp"
#include "socket.hpp"
#include "message.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>


Client::Client(const char* p, const char* h){
    socket = NULL;
    online = false;
    pings = 0;
    port = p;
    hostname = h;
    received = deque<char*>();
    toSend = deque<key_event>();
}

Client::~Client(){
    if (socket) delete socket;
    socket = NULL;
    pings = 0;
    online = false;
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

bool Client::receive(void *buffer, int size){
    char* data = (char*) buffer;
    if (!socket->sockReceive(data, size)){
        return false;
    }
    return true;
}

void Client::queueReceived(char* event){
    received.push_back(event);
}

char* Client::getEventReceived(){
    if (received.empty()) return NULL;
    char* element = received.at(0);
    received.pop_front();
    return element;
}

bool Client::connected(){
    return online;
}

void Client::disconnect(int how){
    if (how == 1 && online) printf("Lost connection with server. Disconnecting...\n");
    socket->sockShutdown(SHUT_RDWR);
    socket->sockClose();
    online = false;
    pings = 0;
}
