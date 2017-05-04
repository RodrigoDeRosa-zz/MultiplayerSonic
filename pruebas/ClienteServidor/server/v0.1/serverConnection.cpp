#include "server.hpp"
#include "serverConnection.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT "8080"

/*Define el addrinfo del servidor. Devuelve NULL en caso de error. */
addrinfo* resolveServerInfo(){
    struct addrinfo hints, *serverInfo;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, PORT, &hints, &serverInfo);
    if (status != 0) return NULL;

    return serverInfo;
}

bool setServerOnline(Server* server){
    /*Se obtiene la informacion del servidor*/
    struct addrinfo *serverInfo;
    serverInfo = resolveServerInfo();
    if (!serverInfo) return false;
    //Se configura el objeto server y se pone online
    if (!server->setInfo(serverInfo)) return false;
    if (!server->setOnline()) return false;
    printf("Server online!\n");
    return true;
}
