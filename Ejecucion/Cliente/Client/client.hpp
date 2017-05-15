#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "socket.hpp"
#include "message.hpp"
#include <sys/socket.h>
#include <deque>
#include "../../../Juego/Juego.hpp"
using namespace std;

class Client{
    private:
        Socket* socket;
        struct addrinfo *serverInfo;
        bool online;
        bool game_on;
        deque<out_message_t*> received;
        deque<key_event> toSend;
        Juego* juego;
    public:
        const char* port;
        const char* hostname;
        int pings;
        Client(const char* p, const char* h, Juego* juego);
        ~Client();
        /*Inicializa el socket del cliente y guarda la direccion del servidor al que
         *se conectará.
        */
        bool setConnectionInfo(struct addrinfo *serverInfo);
        /*Crea su socket e intenta conectarse al servidor cuya información recibe*/
        bool connectToServer();
        /*Encola un evento para enviar al servidor.*/
        void queueToSend(key_event);
        /*Devuelve el proximo evento a enviar. NULL si no hay ninguno*/
        key_event getEventToSend();
        /*Envia el buffer al servidor al que esta conectado.*/
        bool send(void *buffer, int size);
        /*Recibe mensajes del servidor al que esta conectado y lo guarda en el buffer*/
        bool receive(void *buffer, int size, long int dataLen);
        /*Encola un evento recibido desde el servidor.*/
        void queueReceived(out_message_t*);
        /*Devuelve el proximo evento recibido. NULL si no hay ninguno*/
        out_message_t* getEventReceived();
        /*Indica si el cliente esta conectado a un servidor o no.*/
        bool connected();
        /*Se deconecta del servidor. El parametro how vale 1 si es por perdida
        de conexion con el servidor y 0 sino*/
        void disconnect(int how);
        bool gameOn();
        void startGame();
        void endGame();
        /*Devuelve la instancia de Juego que tiene como atributo*/
        Juego* getJuego();
};

#endif /*CLIENT_HPP*/
