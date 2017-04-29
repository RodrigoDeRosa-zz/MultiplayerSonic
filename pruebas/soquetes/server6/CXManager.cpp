
#include "CXManager.hpp"


//singletons
CXManager::CXManager(){
	cxs = map<int,Conexion>();
	game_on = false;
	}
CXManager::~CXManager(){

}
CXManager& CXManager::getInstance(){
		static CXManager instance;
		return instance;}

//**CONEXION**
Conexion::Conexion(int fd,pthread_t read_thread,pthread_t write_thread){
	this->fd=fd;
	this->reader=read_thread;
	this->writer=write_thread;
	this->outEvents= deque<int>();
	this->status=NEWBORN;
}

Conexion::~Conexion(){
	delete &(this->outEvents);
}

string Conexion::getUsername(){
	return this->username;
}

void Conexion::setUsername(string un){
	this->username = un;
}

void Conexion::queueEvent(int event){
	this->outEvents.push_back(event);
}
//end:CONEXION

//**CXManager**

void CXManager::create_cx(int fd,pthread_t read_thread,pthread_t write_thread){
	cxs[fd] = Conexion(fd, read_thread, write_thread);
}


void CXManager::change_cx(int fd,CX_STATUS status){
	cxs[fd].status = status;
}


void CXManager::assign_user(int fd,string str){
	if (cxs[fd].status != NEWBORN){
//		Logger::getInstance().log("se quiso asignar user a una conexion ya establecida");
		return;
	}
	cxs[fd].setUsername(str);
}


void CXManager::assign_user(int fd,const char* str){
	this->assign_user(fd,string(str));
}


void CXManager::clean(){

}

void CXManager::game_is_on(){
	game_on = true;
}
//end:CXManager


//**FUNCIONES DE THREADS**
void* reader_f(void* data) {return NULL;}
void* writer_f(void* data) {return NULL;}
void* accepter_f(void* data){
	return NULL;
}


//end:Funciones de Threads

//**FUNCIONES DE TESTING**
bool CXManager::is_game_on(){
	return game_on;
}
//end:testing
