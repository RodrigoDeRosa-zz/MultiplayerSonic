#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include <sys/socket.h>
#include <deque>
#include <pthread.h>
using namespace std;

/*Funcion del thread del servidor*/
void* eventHandling(void* arg);

/*Singleton*/
class Server{
    private:
        struct addrinfo *serverInfo;
        Socket* accSocket;

        bool online;

        pthread_t eventThread;
        deque<char*> inEvents;
        deque<char*> outEvents;

        //Game* game; //Juego al que se le envian eventos y del cual se reciben

        Server();
        ~Server();
        /*Setea la informacion del servidor*/
        bool setInfo(char* port);
    public:
        /*Obtencion del singleton*/
        static Server& getInstance();
        /*Inicializa la informacion necesaria para poder conectarse*/
        bool init(char* port);
        /*Pone el servidor en linea*/
        bool setOnline();
        /*Acepta una conexion entrante*/
        Socket* accept();
        /*Informa si el servidor esta conectado o no*/
        bool isOnline();
        /*Desconecta al servidor de internet*/
        void disconnect();
        /*Guarda el evento recibido en la cola de eventos*/
        void queueInEvent(char* event);
        /*Guarda un evento en la cola de eventos salientes*/
        void queueOutEvent(char* event);
        /*Devuelve el proximo evento de salida*/
        char* getOutEvent();
        /*Devuelve el proximo evento de entrada*/
        char* getInEvent();
};

#endif /*SERVER_HPP*/
