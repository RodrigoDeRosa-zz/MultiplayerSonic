#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "socket.hpp"
#include <pthread.h>
#include <deque>
#include <unistd.h>
using namespace std;

enum key_event {LEFT, RIGHT, SPACE};

typedef struct in_message{
    int id;
    key_event key;
} in_message_t;

class CXManager;

class Connection{
    private:
        Socket* socket; //Socket sobre el cual se realiza la comunicacion
        bool online;

        pthread_t reader;
        pthread_t writer;
        pthread_t pinger;
        pthread_t controller;

        deque<char*> outEvents;
    public:
        pthread_mutex_t sendLock;
        int pings;
        int id;
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
        void disconnect(int);
};

#endif /*CONNECTION_HPP*/
