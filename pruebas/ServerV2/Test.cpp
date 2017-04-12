#include "Socket.hpp"
#include "Client.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char** argv){
    /*PASAR TAMAÑO DEL MENSAJE COMO PARAMETRO DEL PROGRAMA.
     *PARA PROBAR CON GOOGLE PONER COMO HOSTNAME: "google.com"
     *Y COMO PORT: 80
    */
    Client client;
    string host;
    int port;

    cout << "Enter hostname: ";
    cin >> host;

    cout << "Enter port: ";
    cin >> port;

    client.init();
    client.configServerAddr(host, port);
    client.connect();

    char* sendData = "GET / HTTP/1.1\r\n\r\n";
    client.send(sendData, strlen(sendData));

    char receivedData[1024];
    client.receive(receivedData, atoi(argv[1]));

    cout << "--------------------------------------\n\n";
    cout << receivedData;
    cout << "\n\n-------------------------------------\n\n";

    return 0;
}
