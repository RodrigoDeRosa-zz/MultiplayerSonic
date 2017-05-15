#include "Server/server.hpp"
#include "Server/socket.hpp"
#include "Server/cxManager.hpp"
#include "Server/connection.hpp"
#include "Server/message.hpp"
#include "../../json/JsonLoader.hpp"
#include "../../Control/Control.hpp"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define SERVER()(Server::getInstance())
#define CXM()(CXManager::getInstance())

#define DEFAULT_PATH "serverDefault.json"
#define MAX_CONN 4
#define PRINTLEN 100
#define ONLINE_TIMEOUT 1
#define ACCEPT_TIMEOUT 1

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
    JsonLoader* json = new JsonLoader(path,DEFAULT_PATH);

    const char* port = json->getPort().c_str();

    /*Inicializo el objeto que controla los aspectos del juego*/
    Control* gameControl = new Control();

    if(!SERVER().init(port)){
        printf("Failed to initialize server!\n");
        return 1;
    }
    if(!SERVER().setOnline()){
        printf("Failed to get server online!\n");
        return 1;
    }
    CXM().init(MAX_CONN);

    pthread_t acceptT, eventDistrT;
    /*Se inician los threads de aceptacion de sockets y de distribucion de eventos*/
    pthread_create(&acceptT, NULL, accept, NULL);
    pthread_create(&eventDistrT, NULL, eventDistribution, NULL);

	while(!SERVER().isOnline()){	//POR LAS DUDAS QUE NO ESTUVIERA ONLINE
		sleep(ONLINE_TIMEOUT);
	}

	while(SERVER().isOnline()){
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

