#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>

class Socket{
    private:
        int sockfd;
    public:
        Socket();
        ~Socket();
        /*Crea el socket y guarda el file descriptor en sockfd.
         *(no se hace en el contructor porque puede fallar!).
        */
        bool sockInit();
        /*Conecta el socket al servidor en la dirección recibida*/
        bool sockConnect(struct sockaddr* address, size_t addrLen);
        /*Lee una cadena de bytes de tamaño size del servidor al que esta conectado
         *y lo guarda en el buffer.
        */
        bool sockReceive(char *buffer, int size);
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
};

#endif /*SOCKET_HPP*/
