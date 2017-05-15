#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include "message.hpp" //in_message_t
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
		bool game_is_on;
        pthread_t eventThread;

		pthread_mutex_t inEventsMux;
		pthread_mutex_t outEventsMux;

        deque<in_message_t*> inEvents;
        deque<char*> outEvents;

        //Game* game; //Juego al que se le envian eventos y del cual se reciben

        Server();
        ~Server();
        /*Setea la informacion del servidor*/
        bool setInfo(const char* port);
    public:
        /*Obtencion del singleton*/
        static Server& getInstance();
        /*Inicializa la informacion necesaria para poder conectarse*/
        bool init(const char* port);
        /*Pone el servidor en linea*/
        bool setOnline();
        /*Acepta una conexion entrante*/
        Socket* accept();
        /*Informa si el servidor esta conectado o no*/
        bool isOnline();
        /*Desconecta al servidor de internet*/
        void disconnect();
        /*Guarda el evento recibido en la cola de eventos*/
        void queueInEvent(in_message_t* event);
        /*Guarda un evento en la cola de eventos salientes*/
        void queueOutEvent(char* event);
        /*Devuelve el proximo evento de salida*/
        char* getOutEvent();
        /*Devuelve el proximo evento de entrada*/
        in_message_t* getInEvent();

		//getter y setter de game_running
		bool is_running();
		void start_game();
		void end_game();

};

#endif /*SERVER_HPP*/
