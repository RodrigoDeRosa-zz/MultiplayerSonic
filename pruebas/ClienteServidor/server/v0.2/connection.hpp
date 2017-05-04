#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "socket.hpp"
#include <pthread.h>
#include <deque>
using namespace std;

void* newConnection(void* arg);

class CXManager;

class Connection{
    private:
        Socket* socket; //Socket sobre el cual se realiza la comunicacion
        bool online;
        int id;

        pthread_t reader;
        pthread_t writer;

        deque<char*> outEvents;
    public:
        Connection(Socket*);
        ~Connection();
        /*Recibe un mensaje a traves del socket*/
        bool receiveMessage(char* buffer, int size);
        /*Envia un mensaje a traves del socket*/
        bool sendMessage(char* buffer, int size);
        /*Setea el identificador que se usa como clave en el CXManager*/
        void setID(int);
        /*Agrega un evento a la cola de eventos salientes*/
        void queueOutEvent(char*);
        /*Toma el primer evento de la cola de eventos a enviar*/
        char* getOutEvent();
        bool isOnline();
        void disconnect();
};

#endif /*CONNECTION_HPP*/
