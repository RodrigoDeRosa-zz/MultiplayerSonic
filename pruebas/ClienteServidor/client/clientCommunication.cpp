#include "client.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#define MAXDATASIZE 100

#define SLEEP_T 3000000	//.8 seg
pthread_mutex_t socketLock;

typedef struct thread{
    pthread_t id;
    void* exit_status;
} thread_t;

/*Envia mensajes al servidor cada 1 segundo para notificar que sigue conectado*/
void* ping(void* arg){
    /*Hay que castear el parametro que viene void*/
    Client* client = (Client*) arg;
    char* message = "ping";

    while(client->connected()){
        usleep(SLEEP_T);
        /*Mutex por las dudas que pisar sends haga lio.*/
        pthread_mutex_lock(&socketLock);
        bool status = client->send(message, strlen(message));
        pthread_mutex_unlock(&socketLock);
        if (!status){
            client->disconnect(1);
        }
    }
    return NULL;
}

void* sendMessage(void* arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        char* message = client->getEventToSend();
        if (!message) continue;
        /*Bloquea y envia*/
        pthread_mutex_lock(&socketLock);
        bool status = client->send(message, strlen(message));
        pthread_mutex_unlock(&socketLock);
        if (!status){
            client->disconnect(1);
        }
    }
    return NULL;
}

void* receiveMessage(void* arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        char message[MAXDATASIZE];
        /*Bloquea y envia*/
        bool status = client->receive(message, MAXDATASIZE);
        if (!status){
            client->disconnect(1);
            break;
        }
        client->queueReceived(message);
    }
    return NULL;
}

/*Inicia la comunicacion del cliente con el servidor, creando threads para
 *pingear al servidor, enviar mensajes de la cola de eventos y recibir mensajes
 *del servidor.
*/
void* startCommunication(void* arg){
    Client* client = (Client*) arg;
    /*Se inicializan los mutex*/
    pthread_mutex_init(&socketLock, NULL);

    /*Se comienza a pingear en un thread nuevo.*/
    thread_t pingThread;
    pthread_create(&(pingThread.id), NULL, ping, client);
    /*Se abre el thread para enviar mensajes.*/
    thread_t sendThread;
    pthread_create(&(sendThread.id), NULL, sendMessage, client);
    /*Se abre el thread para recibir mensajes*/
    thread_t receiveThread;
    pthread_create(&(receiveThread.id), NULL, receiveMessage, client);

    /*Los threads terminan solo cuando el cliente se desconecta*/
    pthread_join(pingThread.id, &(pingThread.exit_status));
    pthread_join(sendThread.id, &(sendThread.exit_status));
    pthread_join(receiveThread.id, &(receiveThread.exit_status));
    /*Se destruyen los mutex*/
    pthread_mutex_destroy(&socketLock);

    return NULL;
}
