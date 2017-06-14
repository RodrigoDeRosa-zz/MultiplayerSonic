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
#include "../../../Juego/PantallaTransicion/ConnectionLostStage.hpp"
#include "../../../Juego/PantallaTransicion/GameOverStage.hpp"
#include "../../../Juego/PantallaTransicion/GameWonStage.hpp"
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
            printed = true;
        }
        if (!message){
            usleep(1000);
            continue;
        }
        if (message->ping == GAME_SET) {
            Juego* juego = new Juego( (gameMode)message->id );
            if (message->frame == 1){ client->setReconnected();}
            client->addJuego(juego);
        } else if (message->ping == GAME_START){
            client->getJuego()->nextStage(); //estaba en pantalla de inicio
            client->startGame();
            delete message;
            break;
        } else if (message->ping == PLAYER_SET){
            for (int i = 0; i < message->id; i++){
                client->addPlayer();
                client->getJuego()->addJugador(SSTR(i), "sonic");
            }
        } else if (message->ping == ROCK_SET){
            client->getJuego()->addPiedra(message->posX, message->posY, message->frame, message->id, message->state_frame);
        } else if (message->ping == SPIKE_SET){
            client->getJuego()->addPinche(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == COIN_SET){
            client->getJuego()->addMoneda(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == BONUS_SET){
            client->getJuego()->addBonus(message->posX, message->posY, message->frame, message->id, message->state_frame);
        } else if (message->ping == CRAB_SET){
            client->getJuego()->addCangrejo(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == FLY_SET){
            client->getJuego()->addMosca(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == FISH_SET){
            client->getJuego()->addPez(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == BOSS_SET){
            client->getJuego()->addBossWaves(message->posX, message->posY, message->id, message->state_frame);
            client->getJuego()->addBoss(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == BALL_SET){
            client->getJuego()->addBossBall(message->posX, message->posY, message->id, message->state_frame);
        } else if (message->ping == PLATFORM_SET){
            client->getJuego()->addPlataforma(message->posX, message->posY, message->id, message->state_frame);
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
    pthread_join(viewThreadID, &viewThread_exit);
	pthread_join(eventThreadID, &eventThread_exit);

    return NULL;
}

void* keyControl(void* arg){
    Client* self = (Client*)arg;

	key_event key = KEY_TOTAL;
    SDL_Event e;
	while(self->gameOn()){
        if (self->gameOver() || self->gameWon()) break;
		while(SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
	        	key = QUIT;
                self->endGame();
                self->manuallyClosed = true;
                return NULL;
	        }
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
				switch( e.key.keysym.sym ){
					case SDLK_SPACE: key = SPACE_DOWN; break;
					case SDLK_LEFT: key = LEFT_DOWN; break;
					case SDLK_RIGHT: key = RIGHT_DOWN; break;
					case SDLK_DOWN: key = DOWN_DOWN; break;
                    case SDLK_UP: key = UP_DOWN; break;
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
        else usleep(1000);
        key = KEY_TOTAL;
	}

    return NULL;
}

void* f_view(void* arg){
	Client* self = (Client*) arg;
    int k = 0;
	while (self->gameOn()){
		out_message_t* message = self->getEventReceived();
        if (!message){
            usleep(1000);
            continue;
        }
        if(message->ping == PLAYER_UPDATE){
            self->updatePlayer(message);
            //Se actualiza el score de los equipos si es que hay
            self->getJuego()->updateCoopScore(message->team_rings, message->team_points);
            self->getJuego()->updateTeamScore(message->team, message->team_rings, message->team_points);
            self->getJuego()->updateCamara(message->camPos,0);
        } else if (message->ping == PLAYER_DEAD){
            self->killPlayer(message);
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
        } else if (message->ping == BOSS_UPDATE){
            self->getJuego()->updateBoss(message);
            message->posX = message->posX-125;
            self->getJuego()->updateBossWaves(message);
        } else if (message->ping == BALL_UPDATE){
            self->getJuego()->updateBossBall(message);
        } else if (message->ping == CHANGE_LEVEL){
            k++;
            if (k == 1){
                delete message;
                continue;
            }
            self->getJuego()->nextStage();
        } else if (message->ping == GAME_WON){
            self->gameWon(true);
            delete message;
            break;
        } else if (message->ping == GAME_OVER){
            self->gameOver(true);
            delete message;
            break;
        }
        delete message;
	}
    self->cleanPlayers();

	return NULL;

}

void* runGame(void* arg){
    Client* self = (Client*) arg;
    /*Conexion del cliente al servidor*/
    if(!initializeConnection(self)){
        self->setFailedToConnect(true);
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
    pthread_join(initThreadID, &initThread_exit);
    self->disconnect(0);
    pthread_join(comThreadID, &comThread_exit);

    return NULL;
}

void* viewControl(void* arg){
    Client* self = (Client*) arg;

    SDL_Event e;
    pthread_t game;
	void* exit_status;
    bool running = true;
    while (running){
        //Pantalla de conexion
        while(!self->connected()){
            self->initUnclick();
            if (self->gameWon() || self->gameOver()) self->showConnectionFailure();
            Renderer::getInstance().clear();

            while(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    return NULL; //Se termina la ejecucion
                }
                if (!self->gameWon() && !self->gameOver()){
                    if (self->initProcessEvent(e) != KEY_TOTAL){
                        pthread_create(&game, NULL, runGame, self);
                        usleep(2000); //Espera que intente conectarse
                        self->setInitClicked();
                    }
                }
            }
            if (self->failedToConnect()){
                self->initUnclick();
                self->showConnectionFailure();
                self->renderInit();
                Renderer::getInstance().draw();
                sleep(1);
                self->resetInit();
                self->setFailedToConnect(false);
                continue;
            }
            self->renderInit();
            Renderer::getInstance().draw();
            usleep(1000);
        }
        self->initUnclick();
        while(!self->getJuego() || !self->getJuego()->stageReady()){
            usleep(50000);
        }
        //Pantalla de inicio de juego
        key_event key;
        if (self->getReconnected()){
            while(!self->gameOn()){
                usleep(500000);
            }
        } else {
            while(!self->gameOn()){
                //Si el server se cierra durante la pantalla de start
                if (!self->connected()) break;
                Renderer::getInstance().clear();
				self->getJuego()->unclickInit();
                //Ahora es otro el thread que renderiza
                while(SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        self->disconnect(0);
                        pthread_join(game, &exit_status);
                        return NULL; //Se termina la ejecucion
                    }
                    key = KEY_TOTAL;
                    key = self->getJuego()->processEvent(e);
                }
                if (key != KEY_TOTAL){
                    self->queueToSend(key);
                    self->getJuego()->setInitClicked();
                    self->getJuego()->render();
                    Renderer::getInstance().draw();
                    break;
                }
                self->getJuego()->render();
                Renderer::getInstance().draw();
                usleep(1000);
            }
            while (!self->gameOn()){
                usleep(500000);
            }
        }
        self->getJuego()->unclickInit();
        //Juego
        int k = 0;
        while(self->gameOn()){
            /*Limpiar pantalla*/
            Renderer::getInstance().setDrawColor(255, 255, 255, 1);
            Renderer::getInstance().clear();
            /*Actualizar entidades*/
            if (self->getJuego()->isLevel()){
                self->updatePlayers();
                if (k!=0) k = 0;
            } else{
                if (k <= 2){
                    self->updateTransition();
                    k += 1;
                }
            }
            /*Renderizar*/
            self->getJuego()->render();
            Renderer::getInstance().draw();
            usleep(1000);
        }
        pthread_join(game, &exit_status); //Ahora el control de eventos se hace en otro thread

        if (self->manuallyClosed) running = false;
        else if (self->gameWon()){
            GameWonStage* won = new GameWonStage(1200, 720);
            self->getJuego()->render();
            won->render();
            Renderer::getInstance().draw();
            sleep(2);
            self->deleteJuego();
        } else if (self->gameOver()){
            GameOverStage* over = new GameOverStage(1200, 720);
            self->getJuego()->render();
            over->render();
            Renderer::getInstance().draw();
            sleep(2);
            self->deleteJuego();
        } else{
            Renderer::getInstance().clear();
            ConnectionLostStage* lost = new ConnectionLostStage(1200, 720);
            self->getJuego()->render();
            lost->render();
            Renderer::getInstance().draw();
            sleep(5);
            self->deleteJuego();
        }
    }
    SDLHandler::getInstance().close();

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
    /*Incializacion de SDL*/
    SDLHandler::getInstance().init();
    /*Incializacion de ventana*/
    Window::getInstance().setDimensions(WINDOW_W, WINDOW_H);
    Window::getInstance().init();
    /*Incializacion de renderer*/
    Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);

    /*Objeto cliente a travÃ©s del cual se realizan las comunicaciones con el server*/
    Client* self = new Client(port, hostname);

	/*Thread que controla la vista*/
    pthread_t start;
    void* exit_status;
    pthread_create(&start, NULL, viewControl, self);

    pthread_join(start, &exit_status);
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
