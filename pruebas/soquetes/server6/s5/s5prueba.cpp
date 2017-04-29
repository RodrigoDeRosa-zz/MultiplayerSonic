/*
* SERVER 5-0-3
*/
#include "s5.h"

#define PORT "9034" 
//main
int main(void)
{
	int listener;
	init(PORT,&listener);
    // main loop
	char accept_flag = 1;//si es 0 deja de loopear y sale
	struct accept_loop_data acc_data = fill_accept_data(listener,&accept_flag);
	pthread_t accept_thread;
	pthread_create(&accept_thread,NULL,accept_loop_on_thread,(void*)&acc_data);
	incEvents.push_back(1);
    while(1) {
		//loop infinitoooo
		if (!incEvents.empty()) {
			printf("De la cola de inc events se saca %d\n",incEvents.front());
			incEvents.pop_front();
		}
    }
	printf("out of the main loop\n");
	//termina el juego qcyo
	accept_flag=0;
	pthread_join(accept_thread,NULL);
    return 0;
}
//end:main
