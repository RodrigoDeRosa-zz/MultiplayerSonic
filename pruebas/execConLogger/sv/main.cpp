#include "../../../message.hpp"
#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include "connection.hpp"
#include "../../../json/json/json.h"
#include "../../../json/json/json-forwards.h"
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "../../../Control/Control.hpp"
#include "../../../logger/current/Logger2.hpp"
#define LOGGER()(Logger::getInstance())
using namespace std;

#define SSTR_( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define SERVER()(Server::getInstance())
#define CXM()(CXManager::getInstance())

#define DEFAULT_PATH "serverDefault.json"
#define PRINTLEN 100
#define ONLINE_TIMEOUT 1
#define ACCEPT_TIMEOUT 1


#define DEFAULT_GAME_MODE	INDIVIDUAL

void avisarEmpiezaJuego(Control* gameControl){
    out_message_t* state = new out_message_t;

    char* startMessage = new char[sizeof(out_message_t)];
    memset(state, 0, sizeof(out_message_t));
    state->ping = GAME_START;
    memcpy(startMessage, state, sizeof(out_message_t));
    SERVER().queueOutEvent(startMessage);
    delete state;

    return NULL;
}
void enviarInformacionJuego(Control* gameControl){
    out_message_t* state = new out_message_t;

    char* message = new char[sizeof(out_message_t)];
    memset(state, 0, sizeof(out_message_t));
    state->ping = GAME_SET;
    memcpy(message, state, sizeof(out_message_t));
    SERVER().queueOutEvent(message);
    usleep(1000);

    char* playerSetting = new char[sizeof(out_message_t)];
    memset(state, 0, sizeof(out_message_t));
    state->ping = PLAYER_SET;
    state->id = CXM().actualConnections;
    //el resto de los atributos del estado no importan
    memcpy(playerSetting, state, sizeof(out_message_t));
    SERVER().queueOutEvent(playerSetting);
    usleep(1000);

    vector<out_message_t*> states = gameControl->getEntidadesInitStatus();
    for(int i = 0; i < states.size(); i++){
        char* outState = new char[sizeof(out_message_t)];
        memcpy(outState, states[i], sizeof(out_message_t));
        SERVER().queueOutEvent(outState);
    }
    usleep(5000);
}

void* accept(void* arg){
    Control* control = (Control*) arg;
    /*Ciclo semi infinito de aceptacion (hasta que se cierre el servidor)*/
    bool has_started = false;
    printf("Server now accepting...\n"); //LOGGEAR
	LOGGER().log("Server now accepting",BAJO);
    while(SERVER().isOnline()){
        sleep(ACCEPT_TIMEOUT);
        Socket* socket = SERVER().accept();
        if (!socket) continue;
        /*Se verifica que no este completo el servidor*/
        if (CXM().actualConnections == CXM().maxConnections){
            socket->sockClose();
            continue;
        }
        printf("Connection accepted!\n"); //LOGGEAR
		LOGGER().log("Connection accepted",BAJO);
        /*Se crea un thread para la nueva conexion*/
        Connection* connection = new Connection(socket);
        CXManager::getInstance().addConnection(connection);

        if (!SERVER().is_running && (CXM().actualConnections == CXM().maxConnections)){
            SERVER().startInitializing();
        }

        /*Esto se da cuando se desconecta alguien y otra persona toma su lugar*/
        if (SERVER().is_running() && has_started){
            out_message_t* state = new out_message_t;
            char* message = new char[sizeof(out_message_t)];
            memset(state, 0, sizeof(out_message_t));
            state->ping = GAME_SET;
            memcpy(message, state, sizeof(out_message_t));
            connection->sendMessage(message, sizeof(out_message_t));
            usleep(1000);

            char* playerSetting = new char[sizeof(out_message_t)];
            memset(state, 0, sizeof(out_message_t));
        	state->ping = PLAYER_SET;
        	state->id = CXM().actualConnections;
        	//el resto de los atributos del estado no importan
            memcpy(playerSetting, state, sizeof(out_message_t));
            connection->sendMessage(playerSetting, sizeof(out_message_t));
            usleep(1000);

            char* startMessage = new char[sizeof(out_message_t)];
            memset(state, 0, sizeof(out_message_t));
            state->ping = GAME_START;
            memcpy(startMessage, state, sizeof(out_message_t));
            connection->sendMessage(startMessage, sizeof(out_message_t));
            delete state;

            //Ahora se le avisa al servidor que cierto jugador se reconecto
            control->setPlayerConnection(SSTR_(connection->id), true);
        }
        /*Ahora se setea esto como un flag, porque no quiero que la primera vez que se inicia el
        juego se envie el mensaje de arriba!!!*/
        if(SERVER().is_running()){has_started = true;}
    }

    return NULL;
}

void* eventDistribution(void* arg){
    while(SERVER().isOnline()){
        /*Si hay eventos entrantes en el manager de conexiones*/
        if (CXM().hasInEvents()){
            /*Se los pasa al servidor para que los procese*/
            SERVER().queueInEvent(CXM().getInEvent());
        }
        /*Si hay eventos salientes en el manager de conexiones*/
        if (CXM().hasOutEvents()){
            char* event = CXM().getOutEvent(); //TODO: Hay que definir el tipo de los eventos
            /*Se le pasa a todas las conexiones para que sean enviados a los clientes*/
            for (int i = 0; i < CXM().maxConnections; i++){
                Connection* connection = CXM().getConnection(i);
                if (!connection) continue; //Puede haber conexiones no disponibles
                connection->queueOutEvent(event);
            }
        }
    }
    /*Termina cuando el servidor ya no esta mas online*/
    return NULL;
}

void* inEventsHandle(void* arg);
void* outStatesHandle(void* arg);
void* updateControl(void* arg);

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: ./main <JSONfile>\n");
        return 1;
    }
    /***************************************LECTURA JSON***********************************************************/
    char* path = argv[1];
    /*Lectura del JSON*/
    ifstream in(path);
    Json::Value json;
    //no encuentra el archivo
    if(in.fail()){
        LOGGER().log("No se encontro el archivo .json",BAJO);
        printf("No se encontro el archivo %s\n", path); //LOGGEAR
        in.clear();
        in.open(DEFAULT_PATH);
    }
    //hay un error de sintaxis
    try{
        in >> json;
    }catch(const Json::RuntimeError& e){
        printf("Error de sintaxis.\n"); //LOGGEAR
        LOGGER().log(string("Error de sintaxis en el archivo client.json . Error: \n") + string(e.what()),BAJO);
        ifstream input(DEFAULT_PATH);
        input >> json;
    }
    const char* port = json["port"].asString().c_str();
    int maxServerConns = json["max_connections"].asInt();
    /***************************************FIN LECTURA JSON***********************************************************/

    if(!SERVER().init(port)){
        printf("Failed to initialize server!\n"); //LOGGEAR
		LOGGER().log("Failed to initialize server",BAJO);
        return 1;
    }
    if(!SERVER().setOnline()){
        printf("Failed to get server online!\n"); //LOGGEAR
		LOGGER().log("Failed to get server online",BAJO);
        return 1;
    }

	Control* gameControl = new Control(DEFAULT_GAME_MODE);
    gameControl->crearEntidades();

    CXM().init(maxServerConns);

    pthread_t acceptT, eventDistrT;
    /*Se inician los threads de aceptacion de sockets y de distribucion de eventos*/
    pthread_create(&acceptT, NULL, accept, gameControl);
    pthread_create(&eventDistrT, NULL, eventDistribution, NULL);

	while(!SERVER().isOnline()){	//POR LAS DUDAS QUE NO ESTUVIERA ONLINE
		sleep(ONLINE_TIMEOUT);
	}

	//PARTE DE INICIALIZACION
    while(!SERVER().initializing()){
        usleep(3000);
    }

    enviarInformacionJuego(gameControl);

	while(!SERVER().is_running()){
		usleep(3000);
	}

	avisarEmpiezaJuego(gameControl);

	for (int i = 0; i < CXM().actualConnections ; i++){
		gameControl->addPlayer(SSTR_(i));
	}

    pthread_t inEventT;
    pthread_create(&inEventT, NULL, inEventsHandle, gameControl);
    pthread_t outStateT;
    pthread_create(&outStateT, NULL, outStatesHandle, gameControl);
    pthread_t updateT;
    pthread_create(&updateT, NULL, updateControl, gameControl);

    /*Se espera a que finalicen los threads*/
    void* exit_status;
    pthread_join(inEventT, &exit_status);
    pthread_join(outStateT, &exit_status);
    pthread_join(acceptT, &exit_status);
    pthread_join(eventDistrT, &exit_status);
    pthread_join(updateT, &exit_status);

    return 0;
}

void* updateControl(void* arg){
    Control* gameControl = (Control*) arg;

    while (SERVER().is_running()){
        gameControl->update();
        usleep(2500);
    }


    return NULL;
}

void* inEventsHandle(void* arg){
    Control* gameControl = (Control*) arg;

    while(SERVER().is_running()){
        in_message_t* ev;

		ev = SERVER().getInEvent();
        /*Si hay evento, se procesa.*/
		if (!ev){
            usleep(1000);
            continue;
		}
        if (ev->key == QUIT){
            gameControl->setPlayerConnection(SSTR_(ev->id), false);
            continue;
        }
        gameControl->handleInMessage(ev);
	}

    return NULL;
}

void* outStatesHandle(void* arg){
    Control* gameControl = (Control*) arg;
    while(SERVER().is_running()){
        /*Cada 10msec se envia la informacion del estado de todos los personajes a todos*/
        vector<out_message_t*> states = gameControl->getStatus();
        for(int i = 0; i < states.size(); i++){
            char* outState = new char[sizeof(out_message_t)];
            memcpy(outState, states[i], sizeof(out_message_t));
            SERVER().queueOutEvent(outState);
        }
        usleep(5000);
    }

    return NULL;
}
