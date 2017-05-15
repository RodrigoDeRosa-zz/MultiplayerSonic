#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "../../../Control/Control.hpp"
using namespace std;

#define SSTR_( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define SERVER()(Server::getInstance())
#define CXM()(CXManager::getInstance())

#define DEFAULT_PATH "serverDefault.json"
#define MAX_CONN 2
#define PRINTLEN 100
#define ONLINE_TIMEOUT 1
#define ACCEPT_TIMEOUT 1

void process_dummy(out_message_t* mOut, in_message_t* mIn);//prototipo

void avisarEmpiezaJuego(char* outState){
	printf("ojo que arranca\n");
	out_message_t* state = new out_message_t;

	state->ping=2;
	state->id=CXM().actualConnections;
	//el resto (lo de abajo) no importa
	state->connection=true;
	state->dirX=0;
	state->dirY=0;
	state->posY=0;
	state->posX=0;
    memcpy(outState, state, sizeof(out_message_t));
    delete state;
	SERVER().queueOutEvent(outState);
}

void* accept(void* arg){
    /*Ciclo semi infinito de aceptacion (hasta que se cierre el servidor)*/
    printf("Server now accepting...\n");
    while(SERVER().isOnline()){
        sleep(ACCEPT_TIMEOUT);
        Socket* socket = SERVER().accept();
        if (!socket) continue;
        /*Se verifica que no este completo el servidor*/
        if (CXM().actualConnections == CXM().maxConnections){
            socket->sockClose();
            continue;
        }
        printf("Connection accepted!\n");
        /*Se crea un thread para la nueva conexion*/
        Connection* connection = new Connection(socket);
        CXManager::getInstance().addConnection(connection);

        if (!SERVER().is_running() && (CXM().actualConnections == CXM().maxConnections)){
			SERVER().start_game();		
		}
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


int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: ./main <JSONfile>\n");
        return 1;
    }
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

    if(!SERVER().init(port)){
        printf("Failed to initialize server!\n");
        return 1;
    }
    if(!SERVER().setOnline()){
        printf("Failed to get server online!\n");
        return 1;
    }

	Control* gameControl = new Control();

    CXM().init(MAX_CONN);

    pthread_t acceptT, eventDistrT;
    /*Se inician los threads de aceptacion de sockets y de distribucion de eventos*/
    pthread_create(&acceptT, NULL, accept, NULL);
    pthread_create(&eventDistrT, NULL, eventDistribution, NULL);

	while(!SERVER().isOnline()){	//POR LAS DUDAS QUE NO ESTUVIERA ONLINE
		sleep(ONLINE_TIMEOUT);
	}

	//PARTE DE INICIALIZACION
	while(!SERVER().is_running()){
		usleep(30000);
	}

    char* outState = new char[sizeof(out_message_t)];
	avisarEmpiezaJuego(outState);

	for (int i = 0; i < CXM().actualConnections ; i++){
		gameControl->addPlayer(SSTR_(i));
	}

	//LOOP DEL JUEGO
	while(SERVER().is_running()){
        in_message_t* ev;

		ev = SERVER().getInEvent();
		if(!ev) {
			usleep(3000);
			continue;
		}

        vector<out_message_t*> v = gameControl->handleInMessage(ev);
        for(int i = 0; i < v.size(); i++){
            char* outState = new char[sizeof(out_message_t)];
            memcpy(outState, v[i], sizeof(out_message_t));
            SERVER().queueOutEvent(outState);
		}

	}

    /*Se espera a que finalicen los threads*/
    void* exit_status;
    pthread_join(acceptT, &exit_status);
    pthread_join(eventDistrT, &exit_status);

    return 0;
}

// LA PRIMERA
/* 
void process_dummy(out_message_t* mOut, in_message_t* mIn){

	mOut->ping = 0;
    mOut->id = mIn->id;
    mOut->connection = true;
    mOut->dirX = 0.0;
    mOut->dirY = 0.0;
    mOut->posX = 1.2;
    mOut->posY = 0.0;

}*/

void process_dummy(out_message_t* mOut, in_message_t* mIn){

	mOut->ping = 0;
    mOut->id = mIn->id;
    mOut->connection = true;
    mOut->dirX = 0.0;
    mOut->dirY = 0.0;
    mOut->posX = 0.0;
    mOut->posY = 0.0;
	switch(mIn->key){
		case LEFT_UP:
			mOut->dirX=-1.0;break;
		case RIGHT_UP:
			mOut->dirX=1.0;break;
		case SPACE_UP:
			mOut->dirY=1.0;break;
		case LEFT_DOWN:
			mOut->dirY=-1.0;break;
		case RIGHT_DOWN:
			mOut->posY=100.0;break;
		default: //PING, QUIT o KEY_TOTAL
			//panic!
			mOut->posY=-999.0;break;
	}

}

