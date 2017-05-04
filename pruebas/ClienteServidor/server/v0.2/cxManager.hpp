#ifndef CXMANAGER_HPP
#define CXMANAGER_HPP

#include "connection.hpp"
#include <map>
#include <deque>
using namespace std;

class Connection;

class CXManager{
    private:
        map<int,Connection*> connections;
        deque<int> ids;

        deque<char*> inEvents;
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
        /*Agrega la conexion recibida.*/
        void addConnection(Connection*);
        /*Borra la conexion con dado id*/
        void removeConnection(int id);
        /*Devuelven la conexion con el id pedido*/
        Connection* getConnection(int id);
        /*Devuelve si las colas tienen o no elementos*/
        bool hasInEvents();
        bool hasOutEvents();
        /*Devuelven el primer elemento de la cola*/
        char* getOutEvent();
        char* getInEvent();
        /*Encolan el evento recibido*/
        void queueInEvent(char* event);
        void queueOutEvent(char* event);
};

#endif /*CXMANAGER_HPP*/
