#include "client.hpp"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

#define MAXDATASIZE 100
#define PINGS_PASSED 10
#define SLEEP_T 100000	//.5 seg

pthread_mutex_t socketLock;

typedef struct thread{
    pthread_t id;
    void* exit_status;
} thread_t;

void* connectionControl(void* arg){
    Client* client = (Client*) arg;

    int pings;
    while(client->connected()){
        usleep(PINGS_PASSED*SLEEP_T);
        pings = client->pings;
        /*Chequea si recibio pings en el ultimo segundo y sino desconecta*/
        if(pings > 0) client->pings = 0;
        else{
            client->disconnect(1);
            break;
        }
    }
    return NULL;
}

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
            break;
        }
    }
    return NULL;
}

void* sendMessage(void* arg){
    Client* client = (Client*) arg;

    char* message;
    int msgLen;
    while(client->connected()){
        message = client->getEventToSend();
        if (!message) continue;
        msgLen = strlen(message);
        /*Bloquea y envia*/
        pthread_mutex_lock(&socketLock);
        bool status = client->send(message, msgLen);
        pthread_mutex_unlock(&socketLock);
        if (!status){
            client->disconnect(1);
            break;
        }
        memset(message, 0, msgLen);
    }
    return NULL;
}

void* receiveMessage(void* arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        char message[MAXDATASIZE];
        char receivedMessage[MAXDATASIZE];
        memset(receivedMessage, 0, MAXDATASIZE);
        /*Bloquea y envia*/
        bool status = client->receive(receivedMessage, MAXDATASIZE);
        if (!status){
            client->disconnect(1);
            break;
        }
        memcpy(message, receivedMessage, MAXDATASIZE);
        if (!strcmp(message, "ping") || !strcmp(strtok(message, "\n"), "ping")){
            client->pings++;
            continue;
        }
        printf("Message %s\n", message);
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
    thread_t controlThread;
    pthread_create(&(controlThread.id), NULL, connectionControl, client);

    /*Los threads terminan solo cuando el cliente se desconecta*/
    pthread_join(pingThread.id, &(pingThread.exit_status));
    pthread_join(sendThread.id, &(sendThread.exit_status));
    pthread_join(receiveThread.id, &(receiveThread.exit_status));
    pthread_join(controlThread.id, &(controlThread.exit_status));
    /*Se destruyen los mutex*/
    pthread_mutex_destroy(&socketLock);

    return NULL;
}
