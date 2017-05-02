#include "client.hpp"
#include "clientConnection.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define PORT "8080"
#define HOSTNAME_LENGTH 64

/*Imprime el ip del servidor cuya informacion se recibe luego del mensaje recibido*/
void printHostIP(string message, struct addrinfo* serverInfo){
    char ipstr[INET_ADDRSTRLEN];
    /*Se castea el ai_addr a IPv4*/
    struct sockaddr_in* sockAddr = (struct sockaddr_in*) serverInfo->ai_addr;
    /*Se pasa el ip de network a presentation*/
    inet_ntop(serverInfo->ai_family, &(sockAddr->sin_addr), ipstr, sizeof ipstr);
    printf("%s %s\n", message.c_str(), ipstr);
}

/**Se pide y devuelve el hostname del servidor. (puede ser IP address).*/
char* setHostname(){
    char *hostname = new char[HOSTNAME_LENGTH];
    printf("Hostname: ");
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    strtok(hostname, "\n");

    return hostname;
}

/*Pide un hostname o dirección y obtiene la información sobre dicho servidor.
 *Repite hasta obtener un hostname valido.
 *Devuelve un struct addrinfo
*/
addrinfo* resolveServerInfo(){
    int status;
    struct addrinfo hints, *serverInfo;
    char* hostname;
    /*Se pide un hostname hasta que sea posible conectarse*/
    do{
        /*Primero se guarda el nombre o direccion del servidor al que se quiere conectar*/
        hostname = setHostname();
        printf("Resolving hostname...\n");
        /*Se define el struct que indica como será el addrinfo del server*/
        memset(&hints, 0, sizeof hints);//Se limpia
        hints.ai_family = AF_INET; //IPv4
        hints.ai_socktype = SOCK_STREAM; //TCP
        /*Se guarda la informacion del host*/
        status = getaddrinfo(hostname, PORT, &hints, &serverInfo);
        if (status != 0)
            fprintf(stderr, "Failed to connect! Error: %s\n", gai_strerror(status));
    } while (status != 0);
    delete[](hostname); //Ya no lo necesito.

    printHostIP("Hostname resolved to:", serverInfo);

    return serverInfo;
}

/*Inicializa las variables necesarias para conectar al cliente al servidor y lo
 *conecta al host indicado por consola.
*/
bool initializeConnection(Client* client){
    /*Se obtiene la informacion del servidor al que se quiere conectar.*/
    struct addrinfo *serverInfo;
    serverInfo = resolveServerInfo();
    //Se configura el cliente para conectarse al servidor.
    if (!client->setConnectionInfo(serverInfo)) return false;
    if (!client->connectToServer()) return false;
    printHostIP("Connected to:", serverInfo);
    return true;
}
