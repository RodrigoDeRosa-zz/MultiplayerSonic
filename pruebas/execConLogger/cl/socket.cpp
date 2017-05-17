#include "socket.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

Socket::Socket(){
	receivedBytes=0;
    sockfd = 0;
	buf1 = new char[SOCKET_BUFSZ];
	memset(buf1,0,SOCKET_BUFSZ);
}
Socket::~Socket(){
    //Si el socket no estaba cerrado, lo cierra.
    if (sockfd > 0) sockClose();
    sockfd = 0;
	delete[] buf1;
}

bool Socket::sockInit(){
    //Como todos son IPv4, se crea en ese dominio, de tipo TCP y con protocolo default.
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    return sockfd > 0;
}

bool Socket::sockConnect(struct sockaddr* address, size_t addrLen){
    //Se conecta al servidor en la direccion recibida
    return connect(sockfd, address, addrLen) != -1;
}

//OLD
/*
//se asume dataLen << size
bool Socket::sockReceive(char* buffer, int size, int dataLen){
    ssize_t reception;
	memset(buffer+dataLen, 0, size-dataLen);
    while (receivedBytes < dataLen){ //si los datos recibidos son mas chicos que lo necesario lee mas
        reception = recv(sockfd, buffer + receivedBytes, size - receivedBytes, MSG_NOSIGNAL);
        if (reception < 0) return false;
        if (reception == 0) return false;
        receivedBytes += reception; 
    }
    return true;
}
*/

//NEW
//se asume dataLen << size
bool Socket::sockReceive(char* buffer, int size, int datalen){
    ssize_t reception;
	//se debe cumplir que buf1[0:receivedBytes] tenga un estado valido
	//puede que no entre al while si le sobraron datos suficientes para pasar
	while(receivedBytes < datalen){
		reception = recv(sockfd, buf1 + receivedBytes, SOCKET_BUFSZ - receivedBytes, MSG_NOSIGNAL);
		if (reception == 0) return false;//socket shutdown
		if (reception < 0) return false; //socket ERROR
		receivedBytes+=reception;
	}
	receivedBytes-=datalen;//ahora recB son los datos QUE SOBRAN
	memcpy(buffer,buf1,datalen);
	if (!receivedBytes){//si no sobro nada
		return true;
	}	
	for(int i=0;i<receivedBytes;i++){
		buf1[i]=buf1[i+datalen];
	}
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
