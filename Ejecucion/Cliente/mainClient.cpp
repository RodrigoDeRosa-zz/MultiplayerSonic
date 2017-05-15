#include "Client/clientConnection.hpp"
#include "Client/clientCommunication.hpp"
#include "Client/client.hpp"
#include "Client/message.hpp"
#include "../../json/JsonLoader.hpp"
//#include "../../Juego/Juego.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//int to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define COMMAND_LENGTH 15
#define MESSAGE_LENGTH 40
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define INPUT "message"
#define DEFAULT_PATH "ClientConfigDefault.json"

void* runGame(void* arg){
    Client* self = (Client*) arg;
    /*Conexion del cliente al servidor*/
    if(!initializeConnection(self)){
        printf("Failed to initialize connection. Disconnecting.\n");
        return NULL;
    }
    /*Una vez conectado, empieza a enviar y recibir mensajes en otro thread.*/
    pthread_t comThreadID;
    void* comThread_exit;
    pthread_create(&comThreadID, NULL, startCommunication, self);
    /*Se espera el mensaje con la cantidad de jugadores del servidor*/
    while(!self->gameOn()){
        in_message_t* message = self->getEventReceived();
        if (!message) usleep(10000);
        if (message->ping == 2){
            for (int i = 0; i < message->id; i++){
                self->getJuego()->addJugador(SSTR(i),"sonic");
            }
            self->startGame();
            break;
        }
    }
    /*Espera la finalizacion del thread de comunicacion*/
    pthread_join(comThreadID, &comThread_exit);

    return NULL;
}

void* f_controller(void* arg);
void* f_view(void* arg);
void* gameControl(void* arg);

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: ./clientGame <JSONfile>\n");
        return 1;
    }
    char* path = argv[1];

    //carga de datos del archivo .json
    JsonLoader* json = new JsonLoader(path,DEFAULT_PATH);
    json->setGame();

    const char* port = json->getPort().c_str();
    const char* hostname = json->getHostname().c_str();

    Stage* stage = json->getStage();
    Camara* camara = json->getCamara(stage);

    //Objeto juego que maneja la vista
    Juego* juego = new Juego();
    juego->setStage(stage);
    juego->setCamara(camara);
    Jugadores* jugs = new Jugadores();
    juego->setJugadores(jugs);
    juego->setFactory();

    /*Objeto cliente a través del cual se realizan las comunicaciones con el server*/
    Client* self = new Client(port, hostname, juego);


    bool running = true;
    bool started = false;
    pthread_t initT;
    pthtead_t game_thread;
    void* exit_status;

    printf("If the game is running, type the command you want whenever you need\n");
    printf("Insert a command: ");
    while(running){
        char command[COMMAND_LENGTH];
        fgets(command, COMMAND_LENGTH, stdin);
        strtok(command, "\n");

        if (strcmp(command, CONNECT) == 0 && !self->connected()){
            pthread_create(&initT, NULL, runGame, self);
        } else if (strcmp(command, DISCONNECT) == 0){
            self->disconnect(0);
            pthread_join(initT, &exit_status);
            printf("Disconnected.\n");
        } else if (strcmp(command, EXIT) == 0){
            self->disconnect(0);
            pthread_join(initT, &exit_status);
            running = false;
        }
        if(self->gameOn()){
            pthread_create(&game_thread, NULL, gameControl, self);
        }
    }
    void* exit_status;
    pthread_join(game_thread, &exit_status);
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}

void* gameControl(void* arg){
    SDLHandler::getInstance().init();

    /*Thread de que envia los mensajes de eventos de teclado*/
    pthread_t controller_thread;
    pthread_create(&controller_thread, NULL, f_controller, arg);
    /*Thread que recibe la informacion a dibujar*/
    pthread_t view_thread;
    pthread_create(&view_thread, NULL, f_view, arg);

    void* exit_status;
    pthread_join(view_thread, &exit_status);
    pthread_join(controller_thread, &exit_status);

    return NULL;
}

void* f_controller(void* arg){
    Client* self = (Client*)arg;
    SDL_Event e;
    key_event key = KEY_TOTAL;
    while(self->gameOn()){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
               self->endGame();
               self->disconnect();
            }
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
                switch( e.key.keysym.sym ){
                    case SDLK_SPACE: key = SPACE_DOWN; break;
                    case SDLK_LEFT: key = LEFT_DOWN; break;
                    case SDLK_RIGHT: key = RIGHT_DOWN; break;
                }
            }
            else if( e.type == SDL_KEYUP && e.key.repeat == 0){
                switch( e.key.keysym.sym ){
                    case SDLK_SPACE: key = SPACE_UP; break;
                    case SDLK_LEFT: key = LEFT_UP; break;
                    case SDLK_RIGHT: key = RIGHT_UP; break;
                }
            }
            if (key != KEY_TOTAL) self->queueToSend(key);
        }
    }
    SDLHandler::getInstance().close();

    return NULL;
}

void* f_view(void* arg){
    Client* self = (Client*)arg;
    while(self->gameOn()){
        out_message_t* message = self->getEventReceived();
        if(message == NULL){
            usleep(500);
            continue;
        }
        self->getJuego()->updateJugador(SSTR(message->id),message->dirX,message->dirY,message->posX,message->posY,message->connection);
        self->getJuego()->updateCamara(message->camPos,0);
        Renderer::getInstance().setDrawColor(255, 255, 255, 1);
        Renderer::getInstance().clear();
        self->getJuego()->render();
        Renderer::getInstance().draw();
    }
    //a partir de aca no esta andando el juego (andando==false)
    //cerrar todo lo que haya que cerrar
    return NULL;
}
