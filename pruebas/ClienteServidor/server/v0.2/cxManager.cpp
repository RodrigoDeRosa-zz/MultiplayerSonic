#include "cxManager.hpp"
#include "connection.hpp"
#include <map>
#include <deque>
using namespace std;

CXManager::CXManager(){}
CXManager::~CXManager(){}

CXManager& CXManager::getInstance(){
    static CXManager instance;
    return instance;
}

void CXManager::init(int maxConn){
    maxConnections = maxConn;
    actualConnections = 0;
    /*Esta cola tiene los ids de las conexiones. A medida que se agregan, se
    asignan ids. Si alguna conexion se va, se vuelve a encolar ese id y se le
    da a la proxima conexion que llegue.*/
    for (int i = 0; i < maxConn; i++){
        ids.push_back(i);
    }
}

void CXManager::addConnection(Connection* connection){
    int id = ids.at(0);
    ids.pop_front();
    connection->setID(id);
    /*Se agrega la conexion con su id*/
    connections.insert(make_pair(id, connection));
    actualConnections++;
}

void CXManager::removeConnection(int id){
    connections.erase(id);
    ids.push_back(id);
}

Connection* CXManager::getConnection(int id){
    map<int, Connection*>::iterator it;
    /*Se fija si hay una conexion con ese id. Si no la hay, devuelve NULL*/
    it = connections.find(id);
    if (it != connections.end()) return it->second;
    return NULL;
}

bool CXManager::hasInEvents(){
    return !inEvents.empty();
}

bool CXManager::hasOutEvents(){
    return !outEvents.empty();
}

void CXManager::queueInEvent(char* event){
    inEvents.push_back(event);
}

void CXManager::queueOutEvent(char* event){
    outEvents.push_back(event);
}

char* CXManager::getOutEvent(){
    if (outEvents.empty()) return NULL;
    char* event = outEvents.at(0);
    outEvents.pop_front();
    return event;
}

char* CXManager::getInEvent(){
    if (inEvents.empty()) return NULL;
    char* event = inEvents.at(0);
    inEvents.pop_front();
    return event;
}
