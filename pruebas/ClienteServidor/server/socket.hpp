#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>

class Socket{
    private:
        int sockfd;
        void setSockFD(int);

		int receivedBytes;
		char* buf1;
    public:
        Socket();
        ~Socket();
        /*Crea el socket y guarda el file descriptor en sockfd.
         *(no se hace en el contructor porque puede fallar!).
        */
        bool sockInit();
        /*Asocia al socket a un puerto de la maquina*/
        bool sockBind(struct sockaddr *selfAddr, socklen_t addrLen);
        /*Pasiva al socket para escuchar con una cola maxima de backlog conexiones entrantes*/
        bool sockListen(int backlog);
        /*Acepta una conexión entrante y crea un nuevo socket.*/
        Socket* sockAccept(struct sockaddr *clientAddr, socklen_t *addrLen);
        /*Lee una cadena de bytes de tamaño size del servidor al que esta conectado
         *y lo guarda en el buffer.
        */
        bool sockReceive(char *buffer, int size, int dataLen);
        /*Envia la cadena de bytes del buffer tamaño size al servidor al que esta conectado*/
        bool sockSend(char *buffer, int size);
        /*Desactiva toda o parte de la conexion.
         * @param {how}:
         *      - SHUT_RD : Solo desactiva la lectura
         *      - SHUT_WR : Solo desactiva la escritura
         *      - SHUT_RDWR : Desactiva lectura y escritura
        */
        bool sockShutdown(int how);
        /*Cierra el socket y libera los recursos correspondientes*/
        bool sockClose();
        /*Devuelve el int identificador*/
        int getID();
};

#endif /*SOCKET_HPP*/
