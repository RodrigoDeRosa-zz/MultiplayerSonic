#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <arpa/inet.h>

class Socket{
    private:
        int sockfd;
        void setSockfd(int);
    public:
        Socket();
        ~Socket();
        /*Inicializa el socket.*/
        bool sockInit();
        /*Asocia al socket a una direccion.*/
        bool sockBind(const struct sockaddr* address, socklen_t addrLength);
        /*Marca al socket como pasivo, es decir, que escuche conexiones entrantes.
         * @param {backlog} Cantidad de conexiones a encolar.
        */
        bool sockListen(int backlog);
        /*Genera un socket a partir de la primera de las conexiones encoladas
         *en el socket propio. Para llamar a esta funcion, primero se debe pasivar
         *al socket con listen(). Lo mismo con bind().
         *La direccion recibida es la del cliente que se conecta.
        */
        Socket* sockAccept(struct sockaddr* address, socklen_t* addrLength);
        /*Conecta al socket como cliente a la direccion pasada por address.*/
        bool sockConnect(const struct sockaddr* address, socklen_t addrLength);
        /*Lee una cadena de bytes de tamaño msgLen del socket y la guarda en el buffer
         *recibido por parametro.
        */
        bool sockReceive(char* buffer, int msgLen);
        /*Escribe una cadena de bytes de tamaño msgLen a partir del buffer.*/
        bool sockSend(char* buffer, int msgLen);
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
