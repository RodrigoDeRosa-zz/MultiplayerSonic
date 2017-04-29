#include <stdio.h>
#include "CXManager.hpp"

#define IS_OK(ret)(ret ? "OK" : "FAIL")
#define TEST_MSG "%s da resultado %s\n"

int testGameIsNotOn(){
	return CXManager::getInstance().is_game_on();
}

int testCXManagerCreaCx(){
	int fd_trucho =0;
	pthread_t a,b;
	
	CXManager::getInstance().create_cx(fd_trucho,a,b);

	CXManager::getInstance().assign_user(fd_trucho,"Pepe");

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
	printf(TEST_MSG,"CXManager existe",IS_OK(testCXManagerCreaCx()));
	return 0;
}
