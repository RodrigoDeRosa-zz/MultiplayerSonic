
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
	this->username=string(NONAME);
}

Conexion::~Conexion(){
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
	//cxs[fd] = Conexion(fd, read_thread, write_thread); //esto no anda because C++
	cxs.insert(make_pair(fd,Conexion(fd, read_thread, write_thread)));
}


void CXManager::change_cx(int fd,CX_STATUS status){
	//hay que ponerle cxs.at(key) en vez de cxs[key] tambien because C++
	cxs.at(fd).status = status;
}


void CXManager::assign_user(int fd,string str){
	if (cxs.at(fd).status != NEWBORN){
//		Logger::getInstance().log("se quiso asignar user a una conexion ya establecida");
		return;
	}
	cxs.at(fd).setUsername(str);
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

//**utilidades para los threads

// port we're listening on
#define GET_IN_ADDR(sa) (&(((struct sockaddr_in*)sa)->sin_addr)) // get sockaddr, IPv4
#define BUFSIZE	256
#define TIMEOUT_RET_CODE 0	//esto es un fd pero total 0 siempre esta abierto y es stdin,
							//..deberia andar bien.

#define ACCEPT_TIMEOUT 1000	//mseg

//PARA PERROR REEMPLAZAR POR STRERROR(errno) incluyendo errno.h

//Data hay que castearlo a entero via AS_INT
/*int as_int(void* data){
	return *(int*)(&data);
}*/ //esto es una funcion que hace lo que el define, pero el define es más rapido
#define AS_INT(data)(*(int*)(&data))

//Equivalente a llamar a accept pero con timeout, devuelve TIMEOUT_RET_CODE si expira el tiempo[mseg].
int accept_with_timeout(int listener, struct sockaddr * remoteAddr, socklen_t* addrlenAddr, long mseg){
	fd_set asd;
	FD_ZERO(&asd);
	FD_SET(listener,&asd);
	struct timeval tv;
	tv.tv_sec = 0;
  	tv.tv_usec = 0;
	if (mseg*1000 < mseg) tv.tv_sec = mseg/1000000;
	else tv.tv_usec = mseg*1000;
	switch(select(listener+1, &asd, NULL, NULL, &tv)){
		case -1://error
			perror("select");
			exit(4);
		case 0:	//timeout
			return TIMEOUT_RET_CODE;
		default:
			return accept(listener, remoteAddr,addrlenAddr);
	}
}

//**funciones posta para los threads

void* reader_f(void* data) {
	int fd = AS_INT(data);
	printf("reader thread on fd %d: starting\n",fd);
	//



	//
	printf("reader thread on fd %d: exiting\n",fd);
	return NULL;
}

void* writer_f(void* data) {
	int fd = AS_INT(data);
	printf("writer thread on fd %d: starting\n",fd);
	//


	//
	printf("writer thread on fd %d: exiting\n",fd);
	return NULL;
}


void* accepter_f(void* data){
	int listener = AS_INT(data);
	//printf("accepter thread: starting with ID %lu\n",pthread_self());//DEBUG2
	printf("accepter thread: starting\n");
	//

	struct sockaddr_storage remoteAddr;
	socklen_t addrlen = sizeof remoteAddr;
	int newfd = 0;
	while(true){
		if (false) break; //TODO si no hay que aceptar mas (flag de shutdown?)
		newfd = accept_with_timeout(listener, (struct sockaddr *)&remoteAddr, &addrlen, ACCEPT_TIMEOUT);
		if (newfd == TIMEOUT_RET_CODE) {
			printf("accepter thread: Timeout\n");
			continue;
		}
		if (newfd == -1) {
			perror("accept");
			continue;//TODO esto deberia ser un break y llamar a algo
    	}
		//a partir de aca ya tengo el newfd con el fd de la cx aceptada
		long fd_wrp = newfd;//ESTO ES UN WRAPPER PARA EVITAR WARNINGS
		pthread_t wthread,rthread;
		pthread_create(&rthread,NULL,reader_f,(void*)fd_wrp);
		printf("accepter thread: launched reader for fd %d\n",newfd);//DEBUG2
		pthread_create(&wthread,NULL,writer_f,(void*)fd_wrp);
		printf("accepter thread: launched writer for fd %d\n",newfd);//DEBUG2
		CXManager::getInstance().create_cx(listener,rthread,wthread);
		//printeo que se acepto todo ok
    	char remoteIP[INET6_ADDRSTRLEN];
		printf("accepter thread: new cx created from %s on socket fd %d\n", inet_ntop(remoteAddr.ss_family, GET_IN_ADDR((struct sockaddr*)&remoteAddr), remoteIP, INET6_ADDRSTRLEN), newfd);


	}

	//
	printf("accepter thread: exiting\n");
	return NULL;
}


void init(const char* port, int* listening_fd){
    fd_set master;    // master file descriptor list
    FD_ZERO(&master);    // clear the master set

    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
	int rv;

    struct addrinfo hints, *ai, *p;

    // get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0) {
        fprintf(stderr, "init: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }

        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) {
        fprintf(stderr, "init: failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one
	*listening_fd = listener;
}
//end:Funciones de Threads

//**FUNCIONES DE TESTING**
bool CXManager::is_game_on(){
	return game_on;
}
//end:testing
