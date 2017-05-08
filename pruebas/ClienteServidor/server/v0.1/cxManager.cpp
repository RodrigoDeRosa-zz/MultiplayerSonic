#include "socket.hpp"
#include "cxManager.hpp"
#include <map>
#include <deque>
#include <string>
using namespace std;

CXManager::CXManager(){

}

CXManager::~CXManager(){

}

void CXManager::addConnection(Socket* socket, Server* server){
    cxs.insert(make_pair(socket->getID(), Connection(socket, server)));
}

void CXManager::changeConnectionStatus(Socket* socket, CX_STATUS status){
    cxs.at(socket->getID()).status = status;
}

void CXManager::assignUser(Socket* socket, string username){
    if (cxs.at(socket->getID()).status != NEWBORN){
        //Logger::getInstance().log("se quiso asignar user a una conexion ya establecida");
		return;
	}
	cxs.at(socket->getID()).setUsername(username);
}

void CXManager::clean(){}

void CXManager::gameIsOn(){
    gameOn = true;
}
