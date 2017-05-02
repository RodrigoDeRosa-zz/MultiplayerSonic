#include "cxManager.hpp"
#include "socket.hpp"
#include "server.hpp"
#include <string>
#include <pthread.h>
using namespace std;

Connection::Connection(Socket* skt, Server* sv){
    socket = skt;
    server = sv;
    username = "";
}
Connection::~Connection(){
    if (socket) delete socket;
    socket = NULL;
    username = "";
}

string Connection::getUsername(){
    return username;
}

void Connection::setUsername(string user){
    username = user;
}
