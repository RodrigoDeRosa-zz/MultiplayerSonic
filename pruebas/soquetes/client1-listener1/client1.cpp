/*
** client.c -- a stream socket client demo
*/


/*
*MARTIN: CAMBIAR POR LOGGER DONDE DIGA PERROR/FPRINTF/PRINTF
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "9034" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 
#define GET_IN_ADDR(sa) (&(((struct sockaddr_in*)sa)->sin_addr)) //MARTIN: get IPv4 addr

int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client1 hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;//MARTIN:solo IPv4
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, GET_IN_ADDR((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

	//MARTIN: cx establecida, hablando con el sv
	while(true){
		if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) <= 0) {
			if(numbytes <=-1){
		    perror("recv");
		    exit(1);
			}
			//se cerro la cx
			printf("Server hung up. Exiting...\n");
			break;
		}

		buf[numbytes] = '\0';

		printf("client: received '%s'\n",buf);
	}
	//MARTIN: terminar_cx
    close(sockfd);

    return 0;
}
