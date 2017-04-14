/*
** s4.cpp - falta hacerlo objeto y estamos
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

#define PORT "9034"   // port we're listening on
#define GET_IN_ADDR(sa) (&(((struct sockaddr_in*)sa)->sin_addr)) // get sockaddr, IPv4 
#define BUFSIZE	256
#define TIMEOUT_RET_CODE 0	//esto es un fd pero total 0 siempre esta abierto y es stdin,..
							//..deberia andar bien.

#define ACCEPT_TIMEOUT 1000	//mseg

//PARA PERROR REEMPLAZAR POR STRERROR(errno) incluyendo errno.h


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

//end:DECLARACIONES

//main
int main(void)
{
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
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
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
        fprintf(stderr, "selectserver: failed to bind\n");
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

    // main loop
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;
	char accept_flag = 1;//si es 0 deja de loopear y sale
	struct accept_loop_data acc_data = fill_accept_data(listener,&accept_flag);
	pthread_t accept_thread;
	pthread_create(&accept_thread,NULL,accept_loop_on_thread,(void*)&acc_data);
    for(;;) {
		//loop infinitoooo
    }
	printf("out of the main loop\n");
	//termina el juego qcyo
	accept_flag=0;
	pthread_join(accept_thread,NULL);
    return 0;
}
//end:main


//**************DEFINICIONES**************

//******defs since SERVER4********

//Wrapper para el thread de aceptar
struct accept_loop_data fill_accept_data(int listener,char* keep_looping){
	struct accept_loop_data aux;
	aux.listener=listener;
	aux.keep_looping=keep_looping;
	return aux;
}
//Wrapper para el loop infinito de aceptar new_cx's
void* accept_loop_on_thread(void* casted_data){
	//unpack
	printf("s4 server: started accepting.\n");//DEBUG
	struct accept_loop_data data = *(struct accept_loop_data*)(casted_data);
	for(;;) {
		//printf("FLAG\n");//DEBUG2
		if (!(*data.keep_looping)) break;//ANDARA ESTO? hay que ver si accept es blocking	
										 //no,no anda, pero cambio accept por select para..
										 //..tener timeout y fue	
		loopear_y_manejar2(data.listener);
	}
	printf("s4 server: closing accepting thread.\n");//DEBUG
	return NULL;
}

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

//loopea y acá solo acepta y abre threads para read. Escribir es para los giles.
//Sólo debería necesitar el fd listener.
//Se parece bastante a aceptar_nueva_cx, pero no toca fd_set's.
//DEPRECATED (ideal): master_ptr, fdmax_ptr
void loopear_y_manejar2(int listener){
	struct sockaddr_storage remoteAddr;	//MARTIN: será necesario declararla afuera? no creo.
	socklen_t addrlen = sizeof remoteAddr;
	int newfd = accept_with_timeout(listener, (struct sockaddr *)&remoteAddr, &addrlen, ACCEPT_TIMEOUT);
	//int newfd = accept(listener, (struct sockaddr *)&remoteAddr, &addrlen);
	if (newfd == TIMEOUT_RET_CODE) {
		printf("Timeout\n");//DEBUG2
		return;
	}
	if (newfd == -1) {
		perror("accept");
		return;
    } 
	//a partir de aca ya tengo el newfd con el fd de la cx aceptada
    char remoteIP[INET6_ADDRSTRLEN];
	printf("s4 server: new connection from %s on socket %d\n",					//sigue..
			inet_ntop(remoteAddr.ss_family,GET_IN_ADDR((struct sockaddr*)&remoteAddr),//..
			remoteIP, INET6_ADDRSTRLEN), newfd);
	printf("fd en loopear_y_manejar es: %d\n",newfd);//DEBUG2
	launch_reader_on(newfd);
}

//Se entrega un fd con una new_cx, crea thread y referencias para que ande todo silk smooth
//Todo lo que haga falta saber de esta cx debe setearse acá.
void launch_reader_on(int fd){
	int* c = (int*)malloc(sizeof(int));	//es la unica forma de pasar confiablemente parece
	*c = fd;
	printf("s4 server: launching reader for socket %d.\n",fd);//DEBUG
	pthread_t read_thread;
	printf("fd en launch_reader_on es: %d\n",fd);//DEBUG2
	pthread_create(&read_thread,NULL,read_on_thread,(void*) c);//no se puede pasar un tipo basico.
}
//Se entrega un fd con una new_cx, limpia todo lo referido al thread y demas.
//Si se llama a esto con un fd ya cerrado se ignora la llamada
//MARTIN: si por alguna razon hiciera falta diferenciarlos, se puede agregar un segundo arg..
//..que sea [int CODE] y reaccione distinto segun read_on_thread, HB_timeout, etc. con un switch!
void delete_reader_on(int fd){
	printf("s4 server: closing socket %d.\n",fd);//DEBUG
	close(fd);
}

//Este es el loop del reader thread de un socket
void* read_on_thread(void* fd_ptr){
	int fd = *(int*)(fd_ptr);
	free(fd_ptr);
	//unpack data
	char buf[BUFSIZE];
	int nbytes;
	printf("*fd_ptr en read_on_thread es: %d\n",*(int*)(fd_ptr));//DEBUG2
	printf("fd en read_on_thread es: %d\n",fd);//DEBUG2
	while(1){
		nbytes = recv(fd, buf, sizeof buf, 0);
		if (nbytes <= 0){ //si no hay que leer mas..
			if (nbytes == 0) printf("s4 server: socket %d hung up\n", fd);//..porque se dceo
			else perror("recv");		//..porque fallo el recv
			//OJO!! Si expira el HB_timeout se llama a delete_reader_on, igual que esto, y eso cierra..
			//..el socket, asi que cuando lo quiera leer va a fallar, sin signal.
			break;
		}
		//mando a algun lado lo que hay en buf
		//DATO:Los fd tienen scope de proceso, así que se pueden usar como senderID.
		printf("Socket %d sent: %s\n",fd,buf);//DEBUG
	}
	//cierro la cx
	delete_reader_on(fd);
	return NULL;//qcyo
}
//end: defs since SERVER4



//*******defs hasta selectserver3.5***********

//loopea y hace todo acá(accept, read y send)
void loopear_y_manejar(fd_set* master_ptr,int* fdmax_ptr, int listener){
	fd_set read_fds;
	FD_ZERO(&read_fds);
//start:necesario?
	char buf[BUFSIZE];    // buffer for client data
    int nbytes;
//end:necesario?
	
	read_fds = (*master_ptr);
	if (select((*fdmax_ptr)+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
	}
	for(int i = 0; i<= (*fdmax_ptr); i++){		//for fd i ..
		if (!FD_ISSET(i, &read_fds)) continue;	//.. in read_fds
		//i es o new_cx a aceptar o active_cx con data a interpretar
		if (i == listener)	{//i es new_cx
			aceptar_nueva_cx(master_ptr,fdmax_ptr,listener);
			continue;
		}
		//i es active_cx
		nbytes = recv(i, buf, sizeof buf, 0);
		if (nbytes <= 0){ //si no hay que leer mas..
			if (nbytes == 0) printf("selectserver: socket %d hung up\n", i);//..porque se dceo
			else perror("recv");		//..porque fallo el recv
			terminar_cx(master_ptr,i);
			continue; 
		}
		//i es active_cx y ademas en buf hay data a interpretar
		//INTERPRETO LOS nbytes DE DATOS RECIBIDOS EN buf DESDE EL FD i (hago lo que se me cante)
	
		//en este caso mando a todos salvo el server y el sender
		for(int dest = 0; dest <= *(fdmax_ptr); dest++) {
                    	// send to everyone!
                        if (!FD_ISSET(dest, master_ptr)) continue;
                        // except the listener and ourselves
                        if (dest != listener && dest != i) {
							struct send_one_data data = fill_send_data(buf,nbytes,dest);
                        	pthread_t sendOne_thread;
							pthread_create(&sendOne_thread,NULL,send_one,(void*) &data);
						}
		}
	} //end: for i in read_fds
}

//Recibe todo lo necesario (puerto listener y ref+size del master fd_set) y trata de aceptar..
//..una nueva cx, si no puede hace todo para acomodarla, si lo logra todo queda andando con cx nueva
//Post: la nueva cx se agregó en TODOS LADOS QUE HAGA FALTA
void aceptar_nueva_cx(fd_set* master_ptr, int* fdmax_ptr,int listener) {
	struct sockaddr_storage remoteAddr;	//MARTIN: será necesario declararla afuera? no creo.
	socklen_t addrlen = sizeof remoteAddr;
	int newfd = accept(listener, (struct sockaddr *)&remoteAddr, &addrlen);
	if (newfd == -1) {
		perror("accept");
		return;
       	} 
	FD_SET(newfd, master_ptr); 			// add to master set
	if (newfd > *fdmax_ptr)  *fdmax_ptr = newfd;  // keep track of the max
    char remoteIP[INET6_ADDRSTRLEN];
	printf("selectserver: new connection from %s on socket %d\n",					//sigue..
			inet_ntop(remoteAddr.ss_family,GET_IN_ADDR((struct sockaddr*)&remoteAddr),//..
			remoteIP, INET6_ADDRSTRLEN), newfd);									//..aca termina
}

//cierra el fd del socket y lo saca de la lista de cx_activas
//Post: fd no existe más como cx en NINGUN LADO
void terminar_cx(fd_set* master_ptr,int fd){
	close(fd);
	FD_CLR(fd,master_ptr);
}

struct send_one_data fill_send_data(char* buffer, int nbytes, int fd_dest){
	struct send_one_data aux;
	aux.buffer = buffer;
	aux.nbytes = nbytes;
	aux.fd_dest = fd_dest;
	return aux;
}

void* send_one(void* casted_send_one_data){
	struct send_one_data data = *(struct send_one_data*) (casted_send_one_data);
	if (send(data.fd_dest, data.buffer, data.nbytes, 0) != -1) return NULL;
	perror("send"); 	//si no pudiera enviar las cosas				
}
//end: defs hasta selectserver3.5

//end:DEFINICIONES


