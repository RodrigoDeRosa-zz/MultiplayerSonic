#include "serverCommunication.hpp"
#include "server.hpp"

typedef struct thread{
    pthread_t id;
    void* exit_status;
} thread_t;

void* accept(void* arg){
    Server* server = (Server*) arg;

    while(true){ //La idea seria que sea un 'server->notFull()' u otra cosa asi.
        server->acceptConnection();
    }

    return NULL;
}

void* startCommunication(void* arg){
    Server* server = (Server*) arg;

    /*Se crea un thread donde se aceptan las conexiones*/
    thread_t acceptThread;
    pthread_create(&(acceptThread.id), NULL, accept, server);
    /*Los threads terminan cuando el servidor se desconecta.*/
    pthread_join(acceptThread.id, &(acceptThread.exit_status));

    return NULL;
}
