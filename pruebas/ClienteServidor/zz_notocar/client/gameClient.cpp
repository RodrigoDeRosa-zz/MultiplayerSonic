#include "clientConnection.hpp"
#include "clientCommunication.hpp"
#include "client.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define COMMAND_LENGTH 15
#define MESSAGE_LENGTH 40
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define INPUT "message"

void* printReceived(void *arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        char* message = client->getEventReceived();
        if (!message || strlen(message) == 0) continue;
        printf("Server message: '%s'\n", message);
    }
    return NULL;
}

void* runGame(void* arg){
    Client* self = (Client*) arg;
    /*Conexion del cliente al servidor*/
    if(!initializeConnection(self)){
        printf("Failed to initialize connection. Disconnecting.\n");
        return NULL;
    }
    /*Una vez conectado, empieza a enviar y recibir mensajes en otro thread.*/
    pthread_t comThreadID;
    void* comThread_exit;
    pthread_create(&comThreadID, NULL, startCommunication, self);

    pthread_t printThreadID;
    void* printThread_exit;
    pthread_create(&printThreadID, NULL, printReceived, self);

    /*Espera la finalizacion del thread de comunicacion*/
    pthread_join(comThreadID, &comThread_exit);
    pthread_join(printThreadID, &printThread_exit);

    return NULL;
}

int main(int argc, char** argv){
    /*Objeto cliente a través del cual se realizan las comunicaciones con el server*/
    Client* self = new Client();

    if (argc != 2){
        printf("Usage: ./clientGame <JSONfile>\n");
        return 1;
    }
    printf("JSON file %s loaded!\n", argv[1]);

    bool running = true;
    bool started = false;
    pthread_t game;
    void* exit_status;

    printf("If the game is running, type the command you want whenever you need\n");
    printf("Insert a command: ");
    while(running){
        char command[COMMAND_LENGTH];
		char message[MESSAGE_LENGTH];
        fgets(command, COMMAND_LENGTH, stdin);
        strtok(command, "\n");

        if (strcmp(command, CONNECT) == 0 && !self->connected()){
            pthread_create(&game, NULL, runGame, self);
            started = true;
        } else if (strcmp(command, DISCONNECT) == 0){
            self->disconnect(0);
            pthread_join(game, &exit_status);
            printf("Disconnected.\n");
        } else if (strcmp(command, EXIT) == 0){
            self->disconnect(0);
            pthread_join(game, &exit_status);
            running = false;
        } else if (!strcmp(command, INPUT)){
			printf("Write message to send: ");
			fgets(message, MESSAGE_LENGTH, stdin);
			self->queueToSend(message);
		}
    }

    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
