#ifndef SERVERCOMMUNICATION_HPP
#define SERVERCOMMUNICATION_HPP

/*Inicia la comunicacion del servidor con los clientes, creando threads para
 *acpetar conexiones, enviar mensajes a cada cliente y recibir mensajes de cada
 *cliente.
 *Se espera que el argumento sea un puntero a Server.
*/
void* startCommunication(void* arg);

#endif /*SERVERCOMMUNICATION_HPP*/
