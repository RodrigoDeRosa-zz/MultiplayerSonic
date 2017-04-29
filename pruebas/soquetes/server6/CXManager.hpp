#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/time.h> 	//para timer de select
#include <deque>
#include <map>
#include <string>
//#include "Logger2.hpp"

using namespace std;

#define SV_USER	"SERVER"	//username reservado para el thread aceptador

enum CX_STATUS{NEWBORN,ALIVE,TIMEOUT,ZOMBIE,CLOSED,CX_STATUS_TOTAL};
//NEWBORN: se llamo a create_cx, pero no tiene usuario todavia
//ALIVE: ya tiene usuario, es una cx estable que se comunica
//TIMEOUT: el heartbeat paso el timer y lo avisa por aca
//CLOSED: el client cerro el socket

//!!Si una cx esta TIMEOUT o CLOSED y el juego esta andando, la proxima que conecte la va a reemplazar!

/*typedef struct conexion{
	int	fd;//por mas que sea la key
	CX_STATUS	status;
	pthread reader;
	pthread	writer;
	string usuario;
	deque<int> outEvents;} conexion_t;*/

class Conexion{

	int	fd;
	string	username;
	deque<int> outEvents;
	pthread_t reader;
	pthread_t writer;

  public:
	CX_STATUS status;
	Conexion(int fd,pthread_t read_thread,pthread_t write_thread);
	~Conexion();
	string getUsername();
	void setUsername(string un);
	void queueEvent(int event); 


};

class CXManager{
	CXManager();
	~CXManager();
	map<int,Conexion> cxs;
	bool game_on;
	deque<int> inEvents;

	public:
		static CXManager& getInstance();
		void create_cx(int fd,pthread_t read_thread,pthread_t write_thread);
		void change_cx(int fd,CX_STATUS status);
		void assign_user(int fd,string str);
		void assign_user(int fd,const char* str);
		void clean();
		void game_is_on();
		
		//testing
		bool is_game_on();
};


//FUNCIONES PARA EL MANEJO DE THREADS
//NOTA: hay que ver como pasar el fd en data, data = &fd no funciona, pero void* > int  en size ..
//.. asi que tal vez se puede wrappear
void* reader_f(void* data);
void* writer_f(void* data);
void* accepter_f(void* data);
