#include "../../pruebas/ClienteServidor/client/v0.3/clientConnection.hpp"
#include "../../pruebas/ClienteServidor/client/v0.3/clientCommunication.hpp"
#include "../../pruebas/ClienteServidor/client/v0.3/client.hpp"
#include "../../pruebas/ClienteServidor/client/v0.3/message.hpp"
#include "../../json/JsonLoader.hpp"
#include "../../Juego/Juego.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

#define COMMAND_LENGTH 15
#define MESSAGE_LENGTH 40
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define INPUT "message"
#define DEFAULT_PATH "ClientConfigDefault.json"

//DEBUG
#define CMD_SPAM_10	"spam 10"
#define CMD_SPAM_100 "spam 100"
#define SPAM_SLEEPTIME	500	//[useg]
#define FORMAT1 "Client %d has posX %.3f, posY %.3f, dirX %.3f, dirY %.3f\n"
#define FORMAT2 "Client %d has posX %x, posY %x, dirX %x, dirY %x\n"

//DEBUGGING

void hexdump_raw(out_message_t* msg){
	unsigned char* reg = (unsigned char*) msg;
	for (int i=0;i<sizeof(out_message_t);i++,reg++){
		printf("%x",*reg);
	}
	printf("\n");
}
void hexdump_outmsg(out_message_t* msg){
	unsigned char* reg = (unsigned char*) msg;
	for (int i=0;i<sizeof(out_message_t);i++,reg++){
		switch(i){
			case 0:
				printf("PING\n0-3: "); break;
			case 4:
				printf("\nID\n4-7: "); break;
			case 8:
				printf("\nCONNECTION\n8-11: "); break;
			case 12:
				printf("\nDIR X\n12-15: "); break;
			case 16:
				printf("\nDIR Y\n16-19: "); break;
			case 20:
				printf("\nPOS X\n20-23: "); break;
			case 24:
				printf("\nPOS Y\n24-28: "); break;
		}
		printf("%x",*reg);
	}
	printf("\n");
}
//END:DEBUGGING
void* printReceived(void *arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        out_message_t* message = client->getEventReceived();
        if (!message){
            usleep(1000); //msec
            continue;
        }
		hexdump_raw(message);
		//hexdump_outmsg(message);
        //printf(FORMAT1, message->id, message->posX,message->posY,message->dirX,message->dirY);
        delete message;
    }
    return NULL;
}

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

    pthread_t printThreadID;
    void* printThread_exit;
    pthread_create(&printThreadID, NULL, printReceived, self);

    /*Espera la finalizacion del thread de comunicacion*/
    pthread_join(comThreadID, &comThread_exit);
    pthread_join(printThreadID, &printThread_exit);

    return NULL;
}



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
    
    /*Objeto cliente a través del cual se realizan las comunicaciones con el server*/
    Client* self = new Client(port, hostname);

    //Objeto juego que maneja la vista
    Juego* juego = new Juego();
    juego->setStage(stage);
    juego->setCamara(camara);
    Jugadores* jugs = new Jugadores();
    juego->setJugadores(jugs);
    juego->setFactory();

    bool running = true;
    bool started = false;
    pthread_t game;
    void* exit_status;

    printf("If the game is running, type the command you want whenever you need\n");
    printf("Insert a command: ");
    while(running){
        char command[COMMAND_LENGTH];
        fgets(command, COMMAND_LENGTH, stdin);
        strtok(command, "\n");

        if (strcmp(command, CONNECT) == 0 && !self->connected()){
            pthread_create(&game, NULL, runGame, self);
            started = true;
        } else if (strcmp(command, DISCONNECT) == 0){
            self->disconnect(0);
            pthread_join(game, &exit_status);
            printf("Disconnected.\n");
        } else if (strcmp(command, EXIT) == 0){
            self->disconnect(0);
            pthread_join(game, &exit_status);
            running = false;
        }
        //if(game started){
            SDL_Event e;
            key_event key = KEY_TOTAL;
            while(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                   //SDL_QUIT
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
        //}
    }
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
