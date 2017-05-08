#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BACKLOG 5

Server::Server(){
    accSocket = NULL;
    cxManager = NULL;
    //game = NULL;
}

Server::~Server(){
    if (accSocket) delete accSocket;
    accSocket = NULL;
    if (cxManager) delete cxManager;
    cxManager = NULL;
    /*if (game) delete game
    game = NULL*/
}

bool Server::setInfo(struct addrinfo* srvInfo){
    serverInfo = srvInfo;
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
    return status;
}

bool Server::acceptConnection(){
    struct addrinfo* clientAddr;
    Socket* newSock = accSocket->sockAccept(clientAddr->ai_addr, &clientAddr->ai_addrlen);
    if (!newSock) return false;
    cxManager->addConnection(newSock, this);
    return true;
}
