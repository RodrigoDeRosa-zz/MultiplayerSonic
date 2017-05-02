#ifndef CXMANAGER_HPP
#define CXMANAGER_HPP

#include "socket.hpp"
#include "server.hpp"
#include "connection.hpp"
#include <map>
#include <deque>
#include <string>
using namespace std;

enum CX_STATUS{NEWBORN, ALIVE, TIMEOUT, ZOMBIE, CLOSED, CX_STATUS_TOTAL};
//NEWBORN: se llamo a create_cx, pero no tiene usuario todavia
//ALIVE: ya tiene usuario, es una cx estable que se comunica
//TIMEOUT: el heartbeat paso el timer y lo avisa por aca
//CLOSED: el client cerro el socket
//!!Si una cx esta TIMEOUT o CLOSED y el juego esta andando, la proxima que conecte la va a reemplazar!

class Server;

class Connection{
    private:
        Socket* socket; //Socket sobre el cual se realiza la comunicacion
        Server* server; //Server en el que se creo
        string username;
        pthread_t reader;
        pthread_t writer;
    public:
        CX_STATUS status;
        Connection(Socket*, Server*);
        ~Connection();
        bool receiveMessage();
        bool sendMessage();
        string getUsername();
        void setUsername(string);
};

class CXManager{
    private:
        map<int, Connection> cxs;
        bool gameOn;
        deque<char*> inEvents;
    public:
        CXManager();
        ~CXManager();
        /*Agrega una conexion con el socket recibido.*/
        void addConnection(Socket*, Server*);
        /*Cambia el estado de la conexion a una de las opciones en CX_STATUS*/
        void changeConnectionStatus(Socket*, CX_STATUS);
        /*Asigna un nombre de usuario a una conexion*/
        void assignUser(Socket*, string username);
        void clean();
        void gameIsOn();
};

#endif /*CXMANAGER_HPP*/
