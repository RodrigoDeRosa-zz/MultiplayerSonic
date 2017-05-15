#include "server.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include "connection.hpp"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "Messages.h"

#define SERVER()(Server::getInstance())
#define CXM()(CXManager::getInstance())

#define PORT "9034"
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

//DUMMY QUE RECIBE UN IN_MSG* y OUT_MSG* Y MODIFICA OUT_MSG SEGUN EL IN_MSG
void process_dummy(InMessage* in_msg, OutMessage* out_msg){
	strcpy(out_msg->playerName,in_msg->playerName);
	out_msg->connection=in_msg->connection;
	out_msg->dirX=0.0;
	out_msg->dirY=0.0;
	out_msg->posX=0.0;
	out_msg->posY=0.0;
	switch(in_msg->key){
		case LEFT:
			out_msg->dirX=-1;break;
		case RIGHT:
			out_msg->dirX=1;break;
		case JUMP:
			out_msg->dirY=1;break;
		case QUIT:
			out_msg->posX=-1000;break;
		default:
			break;
	}
}


int main(int argc, char** argv){
	printf("Size of InMessage es %u\n",sizeof(InMessage));//DEBUG
	printf("Size of OutMessage es %u\n",sizeof(OutMessage));//DEBUG
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

	InMessage* ev;
//	ESTO PUEDE LLEGAR A PISARSE SI ENCOLA OTRO SIN MANDAR EL PRIMERO
/*
	char* state = new char[PRINTLEN];
*/
//	LO RESOLVI CON ESTO (1)
	OutMessage* state;
//	end:(1)
	while(SERVER().isOnline()){
		ev = (InMessage*) SERVER().getInEvent();
		if(!ev) {
			usleep(3000);
			continue;
		}
        //ev es un evento entrante, a procesar por el juego
        //snprintf(state, PRINTLEN,"Client %d sent event %d", ev->id, ev->key);

//	Y CON ESTO (2)
		state=new struct out_message;
		//sino tmb se puede hacer new char[sizeof(struct out_message)] creo
//	DESPUES VEMOS COMO HACER PARA BORRARLO UNA VEZ SE HAYA MANDADO A TODOS
//	end:(2)
		
		process_dummy(ev,state);
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
