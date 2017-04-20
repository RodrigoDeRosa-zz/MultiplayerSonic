/*
* SERVER 5-0-2
*/
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

using namespace std;
//**************DECLARACIONES**************

//**hasta selectserver3.5**
void aceptar_nueva_cx(fd_set* master_ptr, int* fdmax_ptr,int listener);

void terminar_cx(fd_set* master_ptr,int fd);

void loopear_y_manejar(fd_set* master_ptr,int* fdmax_ptr, int listener);

struct send_one_data{
	char*	buffer;
	int		nbytes;
	int		fd_dest;};
struct send_one_data fill_send_data(char* buffer, int nbytes, int fd_dest);
void* send_one(void* casted_send_one_data);

//**desde server4**
void loopear_y_manejar2(int listener);
void* read_on_thread(void* fd_ptr);
void delete_reader_on(int fd);
void launch_reader_on(int fd);
void* accept_loop_on_thread(void* casted_data);
struct accept_loop_data{int listener; 
						char* keep_looping;};
struct accept_loop_data fill_accept_data(int listener,char* keep_looping);
int accept_with_timeout(int listener, struct sockaddr * remoteAddr, socklen_t* addrlenAddr, long mseg);

//**desde server5**
void init(const char* port, int* listening_fd);

static deque<int> incEvents = deque<int>();
static deque<int> outEvents = deque<int>();
//end:DECLARACIONES
