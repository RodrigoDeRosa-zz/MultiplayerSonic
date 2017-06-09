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
#include "../../../Juego/PantallaInicio/InitStage.hpp"
#include "../../../Juego/PantallaTransicion/TransitionStageSingle.hpp"
#include "../../../Juego/PantallaTransicion/TransitionStageCoop.hpp"
#include "../../../Juego/PantallaTransicion/TransitionStageTeams.hpp"
#include "../../../Graficos/SDLHandler.hpp"
#include "../../../logger/current/Logger2.hpp"
#include <SDL2/SDL.h>
using namespace std;

//int to string
#define SSTR( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()

#define WINDOW_W 1200
#define WINDOW_H 720
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
        /*if (message->ping == GAME_TYPE){
            //TODO: Setear pantalla de inicio dependiendo el tipo de juego
        }*/
        if (message->ping == GAME_SET) {
            printf("Iniciando juego.\n"); //NO LOGGEAR
            //SDLHandler::getInstance().init();

            JsonLoader* gameJson = new JsonLoader("ejemplo.json","ejemplo2.json");
            //gameJson->setGame();
            //Juego* juego = new Juego();
            //client->addJuego(juego);
            Stage* stage = gameJson->getStage();
            client->getJuego()->addStage(stage);
            client->getJuego()->nextStage();
            Camara* camara_pantalla = gameJson->getCamara(stage);
            client->getJuego()->setCamara(camara_pantalla);
            Jugadores* jugs = new Jugadores();
            client->getJuego()->setJugadores(jugs);
            client->getJuego()->setFactory();
            client->getJuego()->addSpriteGroup("piedras");
            client->getJuego()->addSpriteGroup("pinches");
            client->getJuego()->addEntityGroup("cangrejos");
            client->getJuego()->addEntityGroup("monedas");
            client->getJuego()->addEntityGroup("moscas");
            client->getJuego()->addEntityGroup("peces");
            client->getJuego()->addEntityGroup("bonus");
            client->getJuego()->setStageScore(2);

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
            client->getJuego()->addPiedra(message->posX, message->posY, message->frame, message->id);
        } else if (message->ping == SPIKE_SET){
            client->getJuego()->addPinche(message->posX, message->posY, message->id);
        } else if (message->ping == COIN_SET){
            client->getJuego()->addMoneda(message->posX, message->posY, message->id);
        } else if (message->ping == BONUS_SET){
            client->getJuego()->addBonus(message->posX, message->posY, message->frame, message->id);
        } else if (message->ping == CRAB_SET){
            client->getJuego()->addCangrejo(message->posX, message->posY, message->id);
        } else if (message->ping == FLY_SET){
            client->getJuego()->addMosca(message->posX, message->posY, message->id);
        } else if (message->ping == FISH_SET){
            client->getJuego()->addPez(message->posX, message->posY, message->id);
        }

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
	        	key = QUIT;
                self->endGame();
                break;
	        }
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
				switch( e.key.keysym.sym ){
					case SDLK_SPACE: key = SPACE_DOWN; break;
					case SDLK_LEFT: key = LEFT_DOWN; break;
					case SDLK_RIGHT: key = RIGHT_DOWN; break;
					case SDLK_DOWN: key = DOWN_DOWN; break;
				}
			}
			else if( e.type == SDL_KEYUP && e.key.repeat == 0){
				switch( e.key.keysym.sym ){
					case SDLK_SPACE: key = SPACE_UP; break;
					case SDLK_LEFT: key = LEFT_UP; break;
					case SDLK_RIGHT: key = RIGHT_UP; break;
					case SDLK_DOWN: key = DOWN_UP; break;
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
        k++;
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
        } else if (message->ping == COIN_UPDATE){
            self->getJuego()->updateMoneda(message);
        } else if (message->ping == CRAB_UPDATE){
            self->getJuego()->updateCangrejo(message);
        } else if (message->ping == FLY_UPDATE){
            self->getJuego()->updateMosca(message);
        } else if (message->ping == FISH_UPDATE){
            self->getJuego()->updatePez(message);
        } else if (message->ping == BONUS_UPDATE){
            self->getJuego()->updateBonus(message);
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
    bool showScreen = true;
    SDL_Event e;

    key_event key;
    //printf("Insert a command: ");
	while(running){
        if (showScreen){
            while(SDL_PollEvent(&e)){
    			if (e.type == SDL_QUIT){
                    running = false;
                    break;
    	        }
                key = self->getJuego()->processEvent(e);
                if (key == START_GAME){
                    pthread_create(&game, NULL, runGame, self);
                    showScreen = false;
                }
                if (key == START_TEAM_1) printf("Team 1!\n");
                if (key == START_TEAM_2) printf("Team 2!\n");
            }
            self->getJuego()->renderNoCam();
            Renderer::getInstance().draw();
        }
		/*char command[COMMAND_LENGTH];
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
		}*/
	}
	return NULL;
}

int main(int argc, char** argv){
    if (argc < 2){
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

    /*Incializacion de SDL*/
    SDLHandler::getInstance().init();
    /*Incializacion de ventana*/
    Window::getInstance().setDimensions(WINDOW_W, WINDOW_H);
    Window::getInstance().init();
    /*Incializacion de renderer*/
    Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);
    /*Creacion de la vista*/
    Juego* juego = new Juego();
    /*Pantalla inicio*/
    InitStage* initStage = new InitStage(WINDOW_W, WINDOW_H, 0);
    juego->addStage(initStage);
    /*Se guarda el juego en el cliente*/
    self->addJuego(juego);

	/*Thread que procesa las ordenes de consola*/
	pthread_t console;
    void* exit_status;
	pthread_create(&console, NULL, consoleChat, self);

	pthread_join(console, &exit_status);
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
