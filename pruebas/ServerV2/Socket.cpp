#include "Socket.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

Socket::Socket(){
    sockfd = 0;
}

void Socket::setSockfd(int socket){
    sockfd = socket;
}

bool Socket::sockInit(){
    /*PF_INET --> IPv4
    SOCK_STREAM --> TCP*/
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    return sockfd > 0;
}

bool Socket::sockBind(const struct sockaddr* address, socklen_t addrLength){
    return bind(sockfd, address, addrLength) == 0;
}

bool Socket::sockListen(int backlog){
    return listen(sockfd, backlog) == 0;
}

Socket* Socket::sockAccept(struct sockaddr* address, socklen_t* addrLength){
    int socket = accept(sockfd, address, addrLength);

    if (socket < 0) return NULL;

    Socket* newSock = new Socket();
    newSock->setSockfd(socket);
    return newSock;
}

bool Socket::sockConnect(const struct sockaddr* address, socklen_t addrLength){
    return connect(sockfd, address, addrLength) == 0;
}

bool Socket::sockReceive(char* buffer, int msgLen){
    int receivedBytes = 0;
    ssize_t reception;
    while (receivedBytes < msgLen){
        reception = recv(sockfd, buffer + receivedBytes, msgLen - receivedBytes, MSG_NOSIGNAL);
        if (reception < 0) return false;
        if (reception == 0) break;
        receivedBytes += reception;
        if (buffer[receivedBytes] == '\0') break;
    }
    buffer[receivedBytes] = '\0';
    return true;
}

bool Socket::sockSend(char* buffer, int msgLen){
    int sentBytes = 0;
    ssize_t sent;
    while (sentBytes < msgLen){
        sent = send(sockfd, buffer + sentBytes, msgLen - sentBytes, MSG_NOSIGNAL);
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

Socket::~Socket(){
    if (sockfd > 0){
        sockShutdown(SHUT_RDWR);
        sockClose();
    }
    sockfd = 0;
}
