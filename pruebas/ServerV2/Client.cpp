#include "Client.hpp"
#include "Socket.hpp"
#include "Notifications.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define SOCKET_CREATION_ERROR "Couldn't create client socket!"
#define INVALID_HOST_ERROR "Failed to resolve hostname!"
#define CONNECTION_ERROR "Couldn't connect to server!"
#define DATA_SEND_ERROR "Error sending data!"
#define DATA_RECEIVE_ERROR "Error receiving data!"

Client::Client(){
    socket = NULL;
}

Client::~Client(){
    socket = NULL;
}

bool Client::init(){
    socket = new Socket();
    if (!socket->sockInit()){
        delete socket;
        socket = NULL;
        warning(SOCKET_CREATION_ERROR);
    }
    return socket != NULL;
}

bool Client::configServerAddr(string host, int port){
    /*Configuracion de servAddr*/
    if (inet_addr(host.c_str()) == -1){
        struct hostent* he;
        struct in_addr** addr_list;

        /*Como el host no es una direccion ip, se busca uno con ese nombre*/
        he = gethostbyname(host.c_str());
        if (he == NULL){
            warning(INVALID_HOST_ERROR);
            return false;
        }

        /*Hay que castearlo porque h_addr_list lo tiene en otro formato.*/
        addr_list = (struct in_addr**) he->h_addr_list;
        for (int i = 0; addr_list[i] != NULL; i++){
            serverAddr.sin_addr = *addr_list[i];
            cout << host << " resolved to " << inet_ntoa(*addr_list[i]) << endl;
            break;
        }
    } else serverAddr.sin_addr.s_addr = inet_addr( host.c_str());

    serverAddr.sin_family = AF_INET; //IPv4
    serverAddr.sin_port = htons(port);

    return true;
}

bool Client::connect(){
    if (!socket->sockConnect((struct sockaddr*) &serverAddr, (socklen_t) sizeof(serverAddr))){
        warning(CONNECTION_ERROR);
        return false;
    }
    return true;
}

bool Client::send(char* data, int size){
    if (!socket->sockSend(data, size)){
        warning(DATA_SEND_ERROR);
        return false;
    }
    return true;
}

bool Client::receive(char* data, int size){
    if (!socket->sockReceive(data, size)){
        warning(DATA_RECEIVE_ERROR);
        return false;
    }
    return true;
}
