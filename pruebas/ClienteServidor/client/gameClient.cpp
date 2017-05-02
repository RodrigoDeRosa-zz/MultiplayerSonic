#include "clientConnection.hpp"
#include "clientCommunication.hpp"
#include "client.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* printReceived(void *arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        char* message = client->getEventReceived();
        if (!message || strlen(message) == 0) continue;
        printf("Server message: '%s'\n", message);
    }
    return NULL;
}

int main(void){
    /*Objeto cliente a través del cual se realizan las comunaciones con el server*/
    Client* self = new Client();
    /*Conexion del cliente al servidor*/
    if(!initializeConnection(self)){
        printf("Failed to initialize connection. Disconnecting.\n");
        delete self;
        return 0;
    }
    /*Una vez conectado, empieza a enviar y recibir mensajes en otro thread.*/
    pthread_t comThreadID;
    void* comThread_exit;
    pthread_create(&comThreadID, NULL, startCommunication, self);

    pthread_t printThreadID;
    void* printThread_exit;
    pthread_create(&printThreadID, NULL, printReceived, self);

    sleep(2);
    char* message = "Hello server!";
    self->queueToSend(message);
    sleep(1);
    message = "Here I am!";
    self->queueToSend(message);
    sleep(4);
    self->disconnect(0);

    /*Espera la finalizacion del thread de comunicacion*/
    pthread_join(comThreadID, &comThread_exit);
    pthread_join(printThreadID, &printThread_exit);
    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
