/*
** selectserver.c -- a cheezy multiperson chat server
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

#define PORT "9034"   // port we're listening on
#define GET_IN_ADDR(sa) (&(((struct sockaddr_in*)sa)->sin_addr)) // get sockaddr, IPv4 


//**************DECLARACIONES**************
void aceptar_nueva_cx(fd_set* master_ptr, int* fdmax_ptr,int listener);

void terminar_cx(fd_set* master_ptr,int fd);

void loopear_y_manejar(fd_set* master_ptr,int* fdmax_ptr, int listener);

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
    for(;;) {
		loopear_y_manejar(&master,&fdmax,listener);
    }
    return 0;
}
//end:main


//**************DEFINICIONES**************
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

void loopear_y_manejar(fd_set* master_ptr,int* fdmax_ptr, int listener){
	fd_set read_fds;
	FD_ZERO(&read_fds);
//start:necesario?
	char buf[256];    // buffer for client data
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
                        	if (send(dest, buf, nbytes, 0) == -1) {
                            	perror("send");
							}
						}
		}
	} //end: for i in read_fds
}
//end:DEFINICIONES
