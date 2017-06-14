#include "cxManager.hpp"
#include "connection.hpp"
#include "../../../message.hpp"
#include <map>
#include <deque>
#include <algorithm>
#include <stdio.h>
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
    playersReady = 0;
    /*Esta cola tiene los ids de las conexiones. A medida que se agregan, se
    asignan ids. Si alguna conexion se va, se vuelve a encolar ese id y se le
    da a la proxima conexion que llegue.*/
    for (int i = 0; i < maxConn; i++){
        ids.push_back(i);
    }
	pthread_mutex_init(&inEventsMux,NULL);
	pthread_mutex_init(&outEventsMux,NULL);
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
    actualConnections -= 1;
}

Connection* CXManager::getConnection(int id){
    map<int, Connection*>::iterator it;
    /*Se fija si hay una conexion con ese id. Si no la hay, devuelve NULL*/
    it = connections.find(id);
    if (it != connections.end()) return it->second;
    return NULL;
}

bool CXManager::hasInEvents(){
	pthread_mutex_lock(&inEventsMux);
	bool not_empty = !inEvents.empty();
	pthread_mutex_unlock(&inEventsMux);
    return not_empty;
}


bool CXManager::hasOutEvents(){
	pthread_mutex_lock(&outEventsMux);
	bool not_empty =!outEvents.empty();
	pthread_mutex_unlock(&outEventsMux);
    return not_empty;
}

void CXManager::queueInEvent(in_message_t* event){
	pthread_mutex_lock(&inEventsMux);
    inEvents.push_back(event);
	pthread_mutex_unlock(&inEventsMux);
}

void CXManager::queueOutEvent(char* event){
	pthread_mutex_lock(&outEventsMux);
    outEvents.push_back(event);
	pthread_mutex_unlock(&outEventsMux);
}


char* CXManager::getOutEvent(){
	pthread_mutex_lock(&outEventsMux);
    if (outEvents.empty()) {
		pthread_mutex_unlock(&outEventsMux);
		return NULL;
	}
    char* event = outEvents.at(0);
    outEvents.pop_front();
	pthread_mutex_unlock(&outEventsMux);
    return event;
}

in_message_t* CXManager::getInEvent(){
	pthread_mutex_lock(&inEventsMux);
    if (inEvents.empty()) {
		pthread_mutex_unlock(&inEventsMux);
		return NULL;
	}
    in_message_t* event = inEvents.at(0);
    inEvents.pop_front();
	pthread_mutex_unlock(&inEventsMux);
    return event;
}

void CXManager::disableConnection(int id){
    Connection* connection = getConnection(id);
    if (connection){
        connection->disconnect(0);
    }
    ids.erase(remove(ids.begin(), ids.end(), id), ids.end());
}
