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
#include "../../../message.hpp"
#include "../../../json/JsonLoader.hpp"
#include "../../../Juego/Juego.hpp"
#include "../../../Graficos/SDLHandler.hpp"
#include "../../../logger/current/Logger2.hpp"
#include <SDL2/SDL.h>
using namespace std;

//int to string
#define SSTR( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()

#define COMMAND_LENGTH 15
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define DEFAULT_PATH "clientDefault.json"

#define LOGGER()(Logger::getInstance())

void* f_view(void* arg);
void* keyControl(void* arg);

void* initGame(void *arg){
    Client* client = (Client*) arg;

    bool printed = false;
    while(client->connected()){
        out_message_t* message = client->getEventReceived();
        if (!printed){
            printf("Esperando al resto de los jugadores.\n"); //NO LOGGEAR
            printed = true;
        }
        if (!message){
            usleep(1000);
            continue;
        }
        if (message->ping == GAME_SET) {
            printf("Iniciando juego.\n"); //NO LOGGEAR
            SDLHandler::getInstance().init();

            JsonLoader* gameJson = new JsonLoader("ejemplo.json","ejemplo2.json");
            gameJson->setGame();
            Stage* stage = gameJson->getStage();
            Juego* juego = new Juego();
            juego->addStage(stage);
            Camara* camara_pantalla = gameJson->getCamara(stage);
            juego->setCamara(camara_pantalla);
            Jugadores* jugs = new Jugadores();
            juego->setJugadores(jugs);
            juego->setFactory();

            client->addJuego(juego);
        } else if (message->ping == GAME_START){
            client->startGame();
            delete message;
            break;
        } else if (message->ping == PLAYER_SET){
            for (int i = 0; i < message->id; i++){
                client->addPlayer();
                client->getJuego()->addJugador(SSTR(i), "sonic");
            }
        } else if (message->ping == ROCK_SET){
            client->getJuego()->updateStage("piedras", message->id, message->posX, message->posY);
        }
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
	        	key = QUIT;
                self->endGame();
                break;
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
    int k = 0;
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
            usleep(2000);
            continue;
        }
        if(message->ping == PLAYER_UPDATE){
        	self->updatePlayer(message);
            self->getJuego()->updateCamara(message->camPos,0);
        }
        //renderizar
		self->updatePlayers();
		self->getJuego()->render();
        Renderer::getInstance().draw();
	}
    SDLHandler::getInstance().close();
    self->cleanPlayers();

	return NULL;

}

void* runGame(void* arg){
    Client* self = (Client*) arg;
    /*Conexion del cliente al servidor*/
    if(!initializeConnection(self)){
        printf("Failed to initialize connection. Disconnecting.\n"); //LOGGEAR
		LOGGER().log("Failed to initialize connection. Disconnecting.",BAJO);
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
		fgets(command, COMMAND_LENGTH, stdin);
		strtok(command, "\n");

		if (strcmp(command, CONNECT) == 0 && !self->connected()){
			pthread_create(&game, NULL, runGame, self);
		} else if (strcmp(command, DISCONNECT) == 0 && self->connected()){
            self->endGame();
            usleep(500);
            self->disconnect(0);
			pthread_join(game, &exit_status);
			printf("Disconnected.\n"); //LOGGEAR
			LOGGER().log("Disconnected.",BAJO);
		} else if (strcmp(command, EXIT) == 0){
            self->endGame();
            usleep(500);
			self->disconnect(0);
			pthread_join(game, &exit_status);
			running = false;
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
        LOGGER().log("No se encontro el archivo .json",BAJO);
        //printf("No se encontro el archivo %s\n", path); //LOGGEAR
        in.clear();
        in.open(DEFAULT_PATH);
    }
    //hay un error de sintaxis
    try{
        in >> json;
    }catch(const Json::RuntimeError& e){
        //printf("Error de sintaxis.\n"); //LOGGEAR
        LOGGER().log(string("Error de sintaxis en el archivo client.json . Error: \n") + string(e.what()),BAJO);
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
