#include "Estado.hpp"
#include <stdio.h>
#include <unistd.h>

void print(state_type estado);

int main(){
	Estado* estado = new Estado();
	estado->set(INVENCIBLE);
	for(int i = 0; i<15; i++){
		print(estado->get());
		if(i == 5) estado->set(ESCUDO);
		sleep(1);
	}
	return 0;
}

void print(state_type estado){
	switch (estado){
		case NORMAL:
			printf("Normal \n");
			break;
		case ESCUDO:
			printf("Escudo \n");
			break;
		case INVENCIBLE:
			printf("Invencible \n");
			break;
	}
}