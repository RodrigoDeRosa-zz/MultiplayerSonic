#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include "connection.hpp"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define SERVER()(Server::getInstance())
#define CXM()(CXManager::getInstance())

#define PORT "8080"
#define MAX_CONN 10
#define PRINTLEN 100
#define ONLINE_TIMEOUT 1

void* accept(void* arg){
    int MAX_CONNECTIONS = CXM().maxConnections;
    /*Ciclo semi infinito de aceptacion (hasta que se cierre el servidor)*/
    printf("Server now accepting...\n");
    while(SERVER().isOnline()){
        Socket* socket = SERVER().accept();
        printf("Connection accepted!\n");
        if (!socket) continue;
        /*Se verifica que no este completo el servidor*/
        if (CXM().actualConnections == MAX_CONNECTIONS){
            socket->sockClose();
            continue;
        }
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
    if(!SERVER().init(PORT)){
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

	in_message_t* ev;
	char* state = new char[PRINTLEN];
	char id[]="1";

	while(SERVER().isOnline()){
		ev = SERVER().getInEvent();
		if(!ev) {
			usleep(3000);
			continue;
		}
        //ev es un evento entrante, a procesar por el juego
        snprintf(state, PRINTLEN,"Client %d sent event %d", ev->id, ev->key);
		//state es un evento saliente, que encola el juego
		SERVER().queueOutEvent(state);
	}
    delete[](state);

    /*Se espera a que finalicen los threads*/
    void* exit_status;
    pthread_join(acceptT, &exit_status);
    pthread_join(eventDistrT, &exit_status);

    return 0;
}
