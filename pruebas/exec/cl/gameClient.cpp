#include "clientConnection.hpp"
#include "clientCommunication.hpp"
#include "../../../Graficos/Window.hpp"
#include "../../../Graficos/Renderer.hpp"
#include "client.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include "message.hpp"
#include "../../../json/JsonLoader.hpp"
#include "../../../Juego/Juego.hpp"
#include "../../../Graficos/SDLHandler.hpp"
#include <SDL2/SDL.h>
using namespace std;

//int to string
#define SSTR( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()

#define COMMAND_LENGTH 15
#define MESSAGE_LENGTH 40
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define INPUT "message"
#define DEFAULT_PATH "clientDefault.json"

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

void* f_view(void* arg);
void* keyControl(void* arg);

void* initGame(void *arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        out_message_t* message = client->getEventReceived();
        if (!message){
            usleep(1000);
            continue;
        } else if (message->ping == 2){
            SDLHandler::getInstance().init();

            JsonLoader* gameJson = new JsonLoader("ejemplo.json","ejemplo2.json");
            gameJson->setGame();
            Stage* stage = gameJson->getStage();
            Juego* juego = new Juego();
            juego->setStage(stage);
            Camara* camara_pantalla = gameJson->getCamara(stage);
            juego->setCamara(camara_pantalla);
            Jugadores* jugs = new Jugadores();
            juego->setJugadores(jugs);
            juego->setFactory();

            client->addJuego(juego);

			for(int i = 0; i < message->id; i++){
				client->addPlayer();
				client->getJuego()->addJugador(SSTR(i), "sonic");
			}
			client->startGame();
			hexdump_raw(message);
			break;
		}
		hexdump_raw(message);
        delete message;
    }

   	/*Maneja la vista del jugador*/
	pthread_t viewThreadID;
	void* viewThread_exit;
	pthread_create(&viewThreadID, NULL, f_view, client);

	/*Thread que maneja los eventos de teclado*/
	pthread_t eventThreadID;
	void* eventThread_exit;
	pthread_create(&eventThreadID, NULL, keyControl, client);

	/*Se espera que terminen los threads*/
    pthread_join(viewThreadID, &eventThread_exit);
	pthread_join(eventThreadID, &eventThread_exit);

    return NULL;
}

void* keyControl(void* arg){
    Client* self = (Client*)arg;

	key_event key = KEY_TOTAL;
    SDL_Event e;

	while(self->gameOn()){
		while(SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
	        	//TODO: quit
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
		}
        if (key != KEY_TOTAL) self->queueToSend(key);
        key = KEY_TOTAL;
	}

    return NULL;
}

void* f_view(void* arg){
	Client* self = (Client*) arg;

	while (self->gameOn()){
		/*Limpiar pantalla*/
		Renderer::getInstance().setDrawColor(255, 255, 255, 1);
        Renderer::getInstance().clear();

		out_message_t* message = self->getEventReceived();

        if (!message){
        	//renderizar
        	self->updatePlayers();
			self->getJuego()->render();
        	Renderer::getInstance().draw();
   			usleep(1000);
            continue;
        }
        if(message->ping == 0){

	        float estado;
			if (message->connection == false){
				estado = 0.0;
			}
			else{
				estado = 1.0;
			}
        	self->updatePlayer(message->id, message->dirX, message->dirY, message->posX, message->posY, estado);
            self->getJuego()->updateCamara(message->camPos,0);
        }
        //renderizar
		self->updatePlayers();
		self->getJuego()->render();
        Renderer::getInstance().draw();
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

	/*Espera la orden del servidor para empezar el juego*/
    pthread_t initThreadID;
    void* initThread_exit;
    pthread_create(&initThreadID, NULL, initGame, self);

    /*Espera la finalizacion del thread de comunicacion*/
    pthread_join(comThreadID, &comThread_exit);
	pthread_join(initThreadID, &initThread_exit);

    return NULL;
}

void* consoleChat(void* arg){
	Client* self = (Client*) arg;

	pthread_t game;
	void* exit_status;
	bool running = true;

	printf("If the game is running, type the command you want whenever you need\n");
	printf("Insert a command: ");
	while(running){
		char command[COMMAND_LENGTH];
		char message[MESSAGE_LENGTH];
		fgets(command, COMMAND_LENGTH, stdin);
		strtok(command, "\n");

		if (strcmp(command, CONNECT) == 0 && !self->connected()){
			pthread_create(&game, NULL, runGame, self);
		} else if (strcmp(command, DISCONNECT) == 0){
			self->disconnect(0);
			pthread_join(game, &exit_status);
			printf("Disconnected.\n");
		} else if (strcmp(command, EXIT) == 0){
			self->disconnect(0);
			pthread_join(game, &exit_status);
			running = false;
		} else if (self->gameOn() && !strcmp(command, INPUT)){
			printf("Write message to send: ");
			fgets(message, MESSAGE_LENGTH, stdin);
			key_event key = KEY_TOTAL;
			strtok(message, "\n");
			if (!strcmp(message, "right")) key = RIGHT_UP;
			else if (!strcmp(message, "left")) key = LEFT_UP;
			else if (!strcmp(message, "jump")) key = SPACE_UP;
			else if (!strcmp(message, "up")) key = LEFT_DOWN;
			else if (!strcmp(message, "down")) key = RIGHT_DOWN;
			else if (!strcmp(message, "quit")) key = QUIT;
			if (key != KEY_TOTAL) self->queueToSend(key);
		} else if (!strcmp(command, CMD_SPAM_10)){
				for(int i = 0; i<10; i++){
					key_event key = RIGHT_UP;//MARTIN: hara falta un new o se pasa por valor? veremos
					self->queueToSend(key);
					printf("|%d sent|",i);
					usleep(SPAM_SLEEPTIME);
				}
				printf("\n");
		} else if (!strcmp(command, CMD_SPAM_100)){
				for(int i = 0; i<100; i++){
					key_event key = SPACE_UP;//MARTIN: hara falta un new o se pasa por valor? veremos
					self->queueToSend(key);
					if (i%10 == 0) printf("|%d sent|",i);
					usleep(SPAM_SLEEPTIME);
				}
				printf("\n");
		}
	}
	return NULL;
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: ./clientGame <JSONfile>\n");
        return 1;
    }
	/**********************************************CARGA DE JSON************************************************************/
    char* path = argv[1];
    /*Lectura del JSON*/
    ifstream in(path);
    Json::Value json;
    //no encuentra el archivo
    if(in.fail()){
        //Logger::getInstance().log("No se encontro el archivo .json",BAJO);
        printf("No se encontro el archivo %s\n", path);
        in.clear();
        in.open(DEFAULT_PATH);
    }
    //hay un error de sintaxis
    try{
        in >> json;
    }catch(const Json::RuntimeError& e){
        printf("Error de sintaxis.\n");
        //Logger::getInstance().log(string("Error de sintaxis en el archivo client.json . Error: \n") + string(e.what()),BAJO);
        ifstream input(DEFAULT_PATH);
        input >> json;
    }
    const char* port = json["port"].asString().c_str();
    const char* hostname = json["hostname"].asString().c_str();
	/************************************************FIN CARGA DE JSON*************************************************************/

    /*Objeto cliente a travÃ©s del cual se realizan las comunicaciones con el server*/
    Client* self = new Client(port, hostname);

	/*Thread que procesa las ordenes de consola*/
	pthread_t console;
    void* exit_status;
	pthread_create(&console, NULL, consoleChat, self);

	pthread_join(console, &exit_status);
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
