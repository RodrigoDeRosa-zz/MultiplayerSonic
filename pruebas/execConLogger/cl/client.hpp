#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "socket.hpp"
#include "../../../message.hpp"
#include "../../../Juego/Juego.hpp"
#include "../../../Juego/PantallaInicio/ConnectionStage.hpp"
#include <sys/socket.h>
#include <deque>
#include <SDL2/SDL.h>
#include <vector>
using namespace std;

class Client{
    private:
        Socket* socket;
        struct addrinfo *serverInfo;
        bool online;
        bool gameStarted;
        bool gameSet;
        deque<out_message_t*> received;
        deque<key_event> toSend;
        Juego* juego;
        vector<out_message_t*> players; //Guarda la informacion previa de cada uno
        ConnectionStage* initialStage;
    public:
        const char* port;
        const char* hostname;
        int pings;
        bool manuallyClosed;
        Client(const char* p, const char* h);
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
        Juego* getJuego();
        void addJuego(Juego*);
        void addPlayer();
        void cleanPlayers();
        out_message_t* getPlayer(int id);
        void updatePlayer(out_message_t*);
        void updatePlayers();
        void toggleGameSet();
        bool gameIsSet();
        void renderInit();
        key_event initProcessEvent(SDL_Event);
        void updateTransition();
        void setInitClicked();
};

#endif /*CLIENT_HPP*/
