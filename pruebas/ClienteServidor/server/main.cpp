#include "server.hpp"
#include "serverConnection.hpp"
#include "serverCommunication.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int main(int argc, char** argv){
    Server* self = new Server();

    if (!setServerOnline(self)){
        printf("Failed to get server online. Disconnecting.\n");
        delete self;
        return 0;
    }
    /*Una vez que el servidor esta en linea, se activa el thread de aceptacion
    de conexiones*/
    pthread_t comThreadID;
    void* comThread_exit;
    pthread_create(&comThreadID, NULL, startCommunication, self);

    pthread_join(comThreadID, &comThread_exit);

    delete self;
    return 0;
}
