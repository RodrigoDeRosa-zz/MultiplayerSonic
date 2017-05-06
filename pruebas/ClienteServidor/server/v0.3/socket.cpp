#include "socket.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stddef.h>
#include <stdio.h>

Socket::Socket(){
    sockfd = 0;
}
Socket::~Socket(){
    //Si el socket no estaba cerrado, lo cierra.
    if (sockfd > 0) sockClose();
    sockfd = 0;
}

void Socket::setSockFD(int socket){
    sockfd = socket;
}

bool Socket::sockInit(){
    //Como todos son IPv4, se crea en ese dominio, de tipo TCP y con protocolo default.
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    return sockfd > 0;
}

bool Socket::sockBind(struct sockaddr *selfAddr, socklen_t addrLen){
	int yes=1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
    return bind(sockfd, selfAddr, addrLen) == 0;
}

bool Socket::sockListen(int backlog){
    return listen(sockfd, backlog) == 0;
}

Socket* Socket::sockAccept(struct sockaddr* clientAddr, socklen_t* addrLen){
    int socket = accept(sockfd, clientAddr, addrLen);

    if (socket < 0) return NULL;

    Socket* newSock = new Socket();
    newSock->setSockFD(socket);
    return newSock;
}

bool Socket::sockReceive(char* buffer, int size){
    int receivedBytes = 0;
    ssize_t reception;
    while (receivedBytes < size){
        reception = recv(sockfd, buffer + receivedBytes, size - receivedBytes, MSG_NOSIGNAL);
        if (reception < 0) return false;
        if (reception == 0) break;
        receivedBytes += reception;
        if (buffer[receivedBytes] == '\0') break;
    }
    buffer[receivedBytes] = '\0';
    return true;
}

bool Socket::sockSend(char* buffer, int size){
    int sentBytes = 0;
    ssize_t sent;
    while (sentBytes < size){
        sent = send(sockfd, buffer + sentBytes, size - sentBytes, MSG_NOSIGNAL);
        if (sent < 0) return false;
        sentBytes += sent;
    }
    return true;
}

bool Socket::sockShutdown(int how){
    return shutdown(sockfd, how) == 0;
}

bool Socket::sockClose(){
    return close(sockfd) == 0;
}

int Socket::getID(){
    return sockfd;
}
