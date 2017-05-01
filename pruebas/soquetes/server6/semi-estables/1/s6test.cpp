#include <stdio.h>
#include "CXManager.hpp"

#define IS_OK(ret)(ret ? "OK" : "FAIL")
#define TEST_MSG "%s da resultado %s\n"


#define FD_TRUCHO	0
#define FD_OTRO	 	1

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




//MAIN 
int main(){
	//testing pedorro
	printf(TEST_MSG,"La macro IS_OK con 1",IS_OK(1));
	printf(TEST_MSG,"La macro IS_OK con 0",IS_OK(0));
	printf(TEST_MSG,"La macro IS_OK con true",IS_OK(true));
	printf(TEST_MSG,"La macro IS_OK con false",IS_OK(false));
	printf("\n\n");

	printf(TEST_MSG,"Game no esta ON",IS_OK(testGameIsNotOn()));
	printf(TEST_MSG,"CXManager existe y crea una cx",IS_OK(testCXManagerCreaCx()));
	printf(TEST_MSG,"Se cambia status",IS_OK(testCXManagerCambiaStatus()));
	printf(TEST_MSG,"Se crea otra cx",IS_OK(testCXManagerCreaOtra()));
	return 0;
}
