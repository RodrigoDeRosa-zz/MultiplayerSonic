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

//ORDEN DE PRIORIDAD (desde abajo, segun fs que llaman)
aceptar_nueva_cx() //0		//DONE
interpretar_data_de() //0	//NO SE HACE
terminar_cx() //0			//DONE	
reestablecer_read_fds() //1	//adentro de loopear y manejar (read_fds tiene el scope de select)
IMPLEMENTACION DE for(i in read_fds) //1 //va a ser seguro for+(if not->continue)
loopear_y_manejar() //2

                    
//**************************************************
/*	while(true){
		loopear_y_manejar()
	}

	loopear_y_manejar(){
		reestablecer_read_fds
		select()
		//si salio encontro algo (que no sea error) y toco el read_fds
		for(i in read_fds){
			if (i == listener) {
				aceptar_nueva_cx()
				continue
			}
			//si no es listener, es una cx activa que habla (handle data)
			bytes_leidos=recv()
			if (bytes_leidos <= 0){	//atrapo errores
				if (bytes_leidos == 0) print("se cerro conexion")
				else print("error en read")
				terminar_cx(i)
				continue
			}
			//se leyo data relevante
			interpretar_data_de(data,sender)	//esto no merece una f en sí misma. que sea run_thread..
												//..con la f llamada que corresponda	 
		}
	}
*/
//**************************************************


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
	
	read_fds = *master_ptr;
	if (select((*fdmax_ptr)+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
	}
	for(int i = 0; i<= *fdmax_ptr; i++){		//for fd i ..
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
			terminar_cx(i);
			continue; 
		}
		//i es active_cx y ademas en buf hay data a interpretar
		//INTERPRETO LOS nbytes DE DATOS RECIBIDOS EN buf DESDE EL FD i (hago lo que se me cante)
	
		//en este caso mando a todos salvo el server y el sender
		for(int dest = 0; dest <= fdmax; dest++) {
                    	// send to everyone!
                        if (!FD_ISSET(dest, &master)) continue;
                        // except the listener and ourselves
                        if (int dest != listener && dest != i) {
                        	if (send(dest, buf, nbytes, 0) == -1) {
                            	perror("send");
							}
						}
		}
	} //end: for i in read_fds
}
