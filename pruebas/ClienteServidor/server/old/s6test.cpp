#include <stdio.h>
#include "CXManager.hpp"

#define IS_OK(ret)(ret ? "OK" : "FAIL")
#define TEST_MSG "%s da resultado %s\n"


#define FD_TRUCHO	1000
#define FD_OTRO	 	1001
#define PORT 	"9034"

int testGameIsNotOn(){
	return !CXManager::getInstance().is_game_on();
}

int testCXManagerCreaCx(){
	pthread_t a,b;
	
	CXManager::getInstance().create_cx(FD_TRUCHO,a,b);

	CXManager::getInstance().assign_user(FD_TRUCHO,"Pepe");

	return 1;
}

int testCXManagerCambiaStatus(){
	CXManager::getInstance().change_cx(FD_TRUCHO,ZOMBIE);
	return 1;
}

int testCXManagerCreaOtra(){
	pthread_t c,d;
	CXManager::getInstance().create_cx(FD_OTRO,c,d);
	return 1;
}

int testInit(int* fdAddr){
	init(PORT,fdAddr);
	return 1;
}

int testLaunchAcceptThread(int fd){
	pthread_t athread;
	long fd_wrp = fd;	//wrapper para que no tire warnings
	pthread_create(&athread,NULL,accepter_f,(void*)fd_wrp);
	CXManager::getInstance().create_cx(fd,athread,0);
	CXManager::getInstance().assign_user(fd,SV_USER);
	return 1;	
}

//MAIN 
int main(){
	printf("***PRUEBAS SOBRE CXManager Y SERVER 6 EN GRAL***\n\n");
	//testing pedorro
	printf(TEST_MSG,"La macro IS_OK con 1",IS_OK(1));
	printf(TEST_MSG,"La macro IS_OK con 0",IS_OK(0));
	printf(TEST_MSG,"La macro IS_OK con true",IS_OK(true));
	printf(TEST_MSG,"La macro IS_OK con false",IS_OK(false));
	printf("\n");

	printf(TEST_MSG,"Game no esta ON",IS_OK(testGameIsNotOn()));
	printf(TEST_MSG,"CXManager existe y crea una cx",IS_OK(testCXManagerCreaCx()));
	printf(TEST_MSG,"Se cambia status",IS_OK(testCXManagerCambiaStatus()));
	printf(TEST_MSG,"Se crea otra cx",IS_OK(testCXManagerCreaOtra()));
	printf("\n");
	
	int fd_listen = 0;
	printf(TEST_MSG,"Llamar a Init y volver",IS_OK(testInit(&fd_listen)));
	printf("Ademas fd_listen es el fd %d\n",fd_listen);
	printf(TEST_MSG,"Lanzar el accepter thread",IS_OK(testLaunchAcceptThread(fd_listen)));

	printf("Presione tecla para terminar el programa\n");
	while (!getc(stdin)){};
	return 0;
}
