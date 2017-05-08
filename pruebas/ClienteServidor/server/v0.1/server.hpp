#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include "cxManager.hpp"
#include <sys/socket.h>

class CXManager;

class Server{
    private:
        struct addrinfo *serverInfo;
        Socket* accSocket;
        CXManager* cxManager;
        //Game* game;
    public:
        Server();
        ~Server();
        /*Setea la informacion del servidor*/
        bool setInfo(struct addrinfo*);
        /*Pone el servidor en linea*/
        bool setOnline();
        /*Acepta una conexion entrante*/
        void* acceptConnection(void*);
};

#endif /*SERVER_HPP*/
