#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "socket.hpp"
#include <sys/socket.h>
#include <deque>
using namespace std;

class Client{
    private:
        Socket* socket;
        struct addrinfo *serverInfo;
        bool online;
        deque<char*> received;
        deque<char*> toSend;
    public:
        const char* port;
        const char* hostname;
        int pings;
        Client(const char* p, const char* h);
        ~Client();
        /*Inicializa el socket del cliente y guarda la direccion del servidor al que
         *se conectará.
        */
        bool setConnectionInfo(struct addrinfo *serverInfo);
        /*Crea su socket e intenta conectarse al servidor cuya información recibe*/
        bool connectToServer();
        /*Encola un evento para enviar al servidor.*/
        void queueToSend(char* event);
        /*Devuelve el proximo evento a enviar. NULL si no hay ninguno*/
        char* getEventToSend();
        /*Envia el buffer al servidor al que esta conectado.*/
        bool send(void *buffer, int size);
        /*Recibe mensajes del servidor al que esta conectado y lo guarda en el buffer*/
        bool receive(void *buffer, int size);
        /*Encola un evento recibido desde el servidor.*/
        void queueReceived(char* event);
        /*Devuelve el proximo evento recibido. NULL si no hay ninguno*/
        char* getEventReceived();
        /*Indica si el cliente esta conectado a un servidor o no.*/
        bool connected();
        /*Se deconecta del servidor. El parametro how vale 1 si es por perdida
        de conexion con el servidor y 0 sino*/
        void disconnect(int how);
};

#endif /*CLIENT_HPP*/
