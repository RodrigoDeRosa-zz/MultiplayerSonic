#include "connection.hpp"
#include "../../../message.hpp"
#include "socket.hpp"
#include "cxManager.hpp"
#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <string.h>
#include <stdio.h>
#include "../../../logger/current/Logger2.hpp"
#define LOGGER()(Logger::getInstance())
using namespace std;

#define MAX_DATASIZE 200
#define PINGS_PASSED 5
#define PING_UTIME 100000 //0.1s

void* connectionControl(void* arg){
    Connection* connection = (Connection*) arg;

    int pings;
    while(connection->isOnline()){
        usleep(PINGS_PASSED*PING_UTIME);
        pings = connection->pings;
        /*Chequea si recibio pings en el ultimo segundo y sino desconecta*/
        if(pings > 0) connection->pings = 0;
        else{
            connection->disconnect(0);
            break;
        }
    }
    return NULL;
}

void* ping(void* arg){
    Connection* connection = (Connection*) arg;

    out_message_t message;
    message.ping = PINGO;
    bool status;
    while(connection->isOnline()){
        usleep(PING_UTIME);
        /*Se pasa el ping a char* para enviar via socket*/
        char toSend[sizeof(out_message_t)];
        memcpy(toSend, &message, sizeof(out_message_t));
        /*Mutex por las dudas que pisar sends haga lio.*/
        pthread_mutex_lock(&connection->sendLock);
        status = connection->sendMessage(toSend, sizeof(out_message_t));
        pthread_mutex_unlock(&connection->sendLock);
        if (!status){
            connection->disconnect(1);
            break;
        }
        memset(toSend, 0, sizeof(out_message_t));
    }
    return NULL;
}

void* read(void* arg){
    Connection* connection = (Connection*) arg;
    key_event message;
	char msg_buffer[MAX_DATASIZE];

    while (connection->isOnline()){
        /*Si falla la recepcion se considera que se perdio la conexion*/
        if(!connection->receiveMessage(msg_buffer, MAX_DATASIZE, sizeof(int))){
            connection->disconnect(2);
            break;
        }
		memcpy(&message, msg_buffer, sizeof(int)); //Descarta mensajes que lleguen pegados

        connection->pings++;
        /*Si el mensaje es ping, no se hace nada*/
        if (message == PING){
            continue;
        }
        /*Estructura para que procese el juego*/
        in_message_t* messageStruct = new in_message_t;
        /*Guardamos un char* en in_message_t para que lo procese el juego*/
        messageStruct->id = connection->id;
        /*Identificacion del evento*/
        messageStruct->key = message;
        /*Se guarda el struct*/
        CXManager::getInstance().queueInEvent(messageStruct);
    }

    return NULL;
}

void* write(void* arg){
    /*Esta funcion no maneja out_message_t porque el juego se encarga de castearlo
    a char* y todos los eventos de salida se manejan de esa manera en el servidor*/
    Connection* connection = (Connection*) arg;

    char* message;
    bool status;

    while (connection->isOnline()){
        /*Toma el mensaje de la cola de eventos salientes*/
        message = connection->getOutEvent();
        if (!message) continue; //Si esta vacia la cola, sigue
        /*Si no se puede enviar el mensaje se considera que la conexion esta caida*/
        pthread_mutex_lock(&connection->sendLock);
        status = connection->sendMessage(message, sizeof(out_message_t));
        pthread_mutex_unlock(&connection->sendLock);
        if(!status){
            connection->disconnect(3);
            break;
        }
    }

    return NULL;
}

Connection::Connection(Socket* sock){
    socket = sock;
    online = true;
    pings = 0;
    pthread_mutex_init(&sendLock, NULL);
    /*Se crean los threads de recepcion y envio de la conexion*/
    pthread_create(&reader, NULL, read, this);
    pthread_create(&writer, NULL, write, this);
    pthread_create(&pinger, NULL, ping, this);
    pthread_create(&controller, NULL, connectionControl, this);
}

Connection::~Connection(){

}

void Connection::disconnect(int from){
    //printf("Disconnected from %d\n", from);
    if (online){
		printf("Client %d disconnected.\n", id); //LOGGEAR
		char* logmsg = new char[40];
		sprintf(logmsg,"Client %d disconnected.", id);
		LOGGER().log(string(logmsg),BAJO);
	}
    if (online) CXManager::getInstance().removeConnection(id);
    online = false;

    /*Se envia un mensaje para que se grise el personaje*/
    in_message_t* disconnection = new in_message_t;
    disconnection->id = id;
    disconnection->key = QUIT;
    CXManager::getInstance().queueInEvent(disconnection);

    void* exit_status;
    pthread_join(reader, &exit_status);
    pthread_join(writer, &exit_status);
    pthread_join(pinger, &exit_status);
    pthread_join(controller, &exit_status);
    pthread_mutex_destroy(&sendLock);

    if (socket){
        socket->sockClose();
        socket = NULL;
    }

    id = 0;
    pings = 0;
}

void Connection::setID(int n){
    id = n;
}

bool Connection::isOnline(){
    return online;
}

bool Connection::receiveMessage(char* buffer, int size, long int dataLen){
    if(!socket->sockReceive(buffer, size, dataLen)) return false;
    return true;
}

bool Connection::sendMessage(char* buffer, int size){
    if(!socket->sockSend(buffer, size)) return false;
    return true;
}

void Connection::queueOutEvent(char* event){
    outEvents.push_back(event);
}

char* Connection::getOutEvent(){
    if (outEvents.empty()) return NULL;
    char* event = outEvents.at(0);
    outEvents.pop_front();
    return event;
}
