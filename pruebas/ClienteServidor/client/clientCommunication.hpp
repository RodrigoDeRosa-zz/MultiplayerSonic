#ifndef CLIENTCOMMUNICATION_HPP
#define CLIENTCOMMUNICATION_HPP

/*Inicia la comunicacion del cliente con el servidor, creando threads para
 *pingear al servidor, enviar mensajes de la cola de eventos y recibir mensajes
 *del servidor.
 *Se espera que el argumento sea un puntero a Client.
*/
void* startCommunication(void* arg);

#endif /*CLIENTCOMMUNICATION_HPP*/
