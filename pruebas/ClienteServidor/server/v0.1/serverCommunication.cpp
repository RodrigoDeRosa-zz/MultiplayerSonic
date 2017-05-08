#include "serverCommunication.hpp"
#include "server.hpp"

#define MAXTHREADS 10

typedef struct thread{
    pthread_t id;
    void* exit_status;
} thread_t;

void* mainAccept(void* arg){
    Server* server = (Server*) arg;

    thread_t threads[MAXTHREADS];
    int threadNo = 0;
    while(server->online()){ //La idea seria que sea un 'server->notFull()' u otra cosa asi.
        if(!server->acceptConnection()) continue;
        pthread_create(&(threads.[threadNo]), NULL, accept, server);
        threadNo++;
    }

    return NULL;
}

void* startCommunication(void* arg){
    Server* server = (Server*) arg;

    /*Se crea un thread donde se aceptan las conexiones*/
    thread_t acceptThread;
    pthread_create(&(acceptThread.id), NULL, mainAccept, server);
    /*Los threads terminan cuando el servidor se desconecta.*/
    pthread_join(acceptThread.id, &(acceptThread.exit_status));

    return NULL;
}
