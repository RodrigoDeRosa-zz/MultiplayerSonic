#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


/*
*MARTIN: CAMBIAR POR LOGGER DONDE DIGA PERROR/FPRINTF/PRINTF
*/


#define PORT "3490"  // the port users will be connecting to

//MARTIN: por las dudas, CX = connection/conexion
#define MAX_INC_CXS 10     // how many pending connections queue will hold

void sigchld_handler(int s){
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
//MARTIN: SIEMPRE VA A SER IPv4, ASI QUE SIEMPRE sa_family = AF_INET
void *get_in_addr(struct sockaddr *sa){
	return &(((struct sockaddr_in*)sa)->sin_addr);    
}

int main(void)
{
    int sockfd, new_fd;  // listen on sockfd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

	//MARTIN: empieza(init del sv)
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; 	//MARTIN: vamos a usar IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");			
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");				
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");				
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");		
        exit(1);
    }

    if (listen(sockfd, MAX_INC_CXS) == -1) {
        perror("listen");					
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");					
        exit(1);
    }

	//MARTIN: fin(init del sv)


    printf("server: waiting for connections...\n");

	//MARTIN: para modular: a partir de aca solo se usan their_addr,sockfd, s(sin su valor)

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");					
            continue;
        }

        inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *)&their_addr), 
		s, sizeof s);
        printf("server: got connection from %s\n", s);			
	//MARTIN: tener en cuenta que va a ir aceptando cxs NUEVAS acá, como handlearlas es otra.	
	


	//MARTIN: por qué hace falta un fork? no debiera ser necesario
	//MARTIN: voy a ver si se puede sacar y en todo caso llamar a thread(handle_cx)
        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            if (send(new_fd, "Hello, world!", 13, 0) == -1)	//MARTIN: msg a enviar
                perror("send");					
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
