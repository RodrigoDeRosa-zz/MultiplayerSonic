#include "Client/clientConnection.hpp"
#include "Client/clientCommunication.hpp"
#include "Client/client.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include "Client/message.hpp"
#include "../../json/json/json.h"
#include "../../json/json/json-forwards.h"
using namespace std;

#define COMMAND_LENGTH 15
#define MESSAGE_LENGTH 40
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define EXIT "exit"
#define INPUT "message"
#define DEFAULT_PATH "clientDefault.json"

//DEBUG
#define CMD_SPAM_10	"spam 10"
#define CMD_SPAM_100 "spam 100"
#define SPAM_SLEEPTIME	500	//[useg]
#define FORMAT1 "Client %d has posX %.3f, posY %.3f, dirX %.3f, dirY %.3f\n"
#define FORMAT2 "Client %d has posX %x, posY %x, dirX %x, dirY %x\n"

//DEBUGGING

void hexdump_raw(out_message_t* msg){
	unsigned char* reg = (unsigned char*) msg;
	for (int i=0;i<sizeof(out_message_t);i++,reg++){
		printf("%x",*reg);
	}
	printf("\n");
}
void hexdump_outmsg(out_message_t* msg){
	unsigned char* reg = (unsigned char*) msg;
	for (int i=0;i<sizeof(out_message_t);i++,reg++){
		switch(i){
			case 0:
				printf("PING\n0-3: "); break;
			case 4:
				printf("\nID\n4-7: "); break;
			case 8:
				printf("\nCONNECTION\n8-11: "); break;
			case 12:
				printf("\nDIR X\n12-15: "); break;
			case 16:
				printf("\nDIR Y\n16-19: "); break;
			case 20:
				printf("\nPOS X\n20-23: "); break;
			case 24:
				printf("\nPOS Y\n24-28: "); break;
		}
		printf("%x",*reg);
	}
	printf("\n");
}
//END:DEBUGGING
void* printReceived(void *arg){
    Client* client = (Client*) arg;

    while(client->connected()){
        out_message_t* message = client->getEventReceived();
        if (!message){
            usleep(1000); //msec
            continue;
        }
		hexdump_raw(message);
		//hexdump_outmsg(message);
        //printf(FORMAT1, message->id, message->posX,message->posY,message->dirX,message->dirY);
        delete message;
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
    if (argc != 2){
        printf("Usage: ./clientGame <JSONfile>\n");
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
    const char* hostname = json["hostname"].asString().c_str();
    /*Objeto cliente a través del cual se realizan las comunicaciones con el server*/
    Client* self = new Client(port, hostname,NULL);

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
            key_event key = KEY_TOTAL;
            strtok(message, "\n");
            if (!strcmp(message, "right")) key = RIGHT_UP;
            else if (!strcmp(message, "left")) key = LEFT_UP;
            else if (!strcmp(message, "jump")) key = SPACE_UP;
            else if (!strcmp(message, "up")) key = LEFT_DOWN;
            else if (!strcmp(message, "down")) key = RIGHT_DOWN;
            else if (!strcmp(message, "quit")) key = QUIT;
            if (key != KEY_TOTAL) self->queueToSend(key);
		}	else if (!strcmp(command, CMD_SPAM_10)){
				for(int i = 0; i<10; i++){
					key_event key = RIGHT_UP;//MARTIN: hara falta un new o se pasa por valor? veremos
					self->queueToSend(key);
					printf("|%d sent|",i);
					usleep(SPAM_SLEEPTIME);
				}
				printf("\n");
		}   else if (!strcmp(command, CMD_SPAM_100)){
				for(int i = 0; i<100; i++){
					key_event key = SPACE_UP;//MARTIN: hara falta un new o se pasa por valor? veremos
					self->queueToSend(key);
					if (i%10 == 0) printf("|%d sent|",i);
					usleep(SPAM_SLEEPTIME);
				}
				printf("\n");
		}
    }

    /*Destruye el objeto cliente*/
    delete self;

    return 0;
}
