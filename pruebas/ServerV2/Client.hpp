#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Socket.hpp"
#include <sys/socket.h>
#include <string>
using namespace std;

class Client{
    private:
        Socket* socket;
        struct sockaddr_in serverAddr;
    public:
        Client();
        ~Client();
        /*Inicializa el socket del cliente*/
        bool init();
        /*Configura la direccion del servidor al que se conectara.*/
        bool configServerAddr(string host, int port);
        /*Intenta conectarse al servidor. ALERT: Primero debe configurarse la
         *direccion del mismo.
        */
        bool connect();
        /*Envia el string recibido al servidor al que se conecto.*/
        bool send(char* data, int size);
        /*Recibe un string del servidor al que esta conectado*/
        bool receive(char* data, int size);
};

#endif /*CLIENT_HPP*/
