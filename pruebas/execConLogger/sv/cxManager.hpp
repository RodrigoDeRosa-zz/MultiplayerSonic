#ifndef CXMANAGER_HPP
#define CXMANAGER_HPP

#include "connection.hpp"
#include "../../../message.hpp"
#include <map>
#include <deque>
using namespace std;

class Connection;

class CXManager{
    private:
        map<int,Connection*> connections;
        deque<int> ids;

		pthread_mutex_t inEventsMux;
		pthread_mutex_t outEventsMux;

        deque<in_message_t*> inEvents;
        deque<char*> outEvents;

        CXManager();
        ~CXManager();
    public:
        /*Metodo de obtencion del singleton*/
        static CXManager& getInstance();
        /*Setea las variables necesarias para la inicializacion*/
        void init(int maxConn);
        /*Maxima cantidad de conexiones aceptadas y conexiones actuales*/
        int maxConnections;
        int actualConnections;
        int playersReady;
        /*Agrega la conexion recibida.*/
        void addConnection(Connection*);
        /*Borra la conexion con dado id*/
        void removeConnection(int id);
        /*Devuelve el mapa de conexiones actual*/
        map<int, Connection*> getConnections();
        /*Devuelven la conexion con el id pedido*/
        Connection* getConnection(int id);
        /*Devuelve si las colas tienen o no elementos*/
        bool hasInEvents();
        bool hasOutEvents();
        /*Devuelven el primer elemento de la cola*/
        char* getOutEvent();
        in_message_t* getInEvent();
        /*Encolan el evento recibido*/
        void queueInEvent(in_message_t* event);
        void queueOutEvent(char* event);
        /*Resta la cantidad de conexiones posibles*/
        void disableConnection(int id);
};

#endif /*CXMANAGER_HPP*/
