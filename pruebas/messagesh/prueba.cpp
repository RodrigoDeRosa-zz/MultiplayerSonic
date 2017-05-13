#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include "message.hpp"
using namespace std;

void hexdump_outmsg(out_message_t* msg){
	unsigned char* reg = (unsigned char*) msg;
	for (int i=0;i<sizeof(out_message_t);i++,reg++){
			if (reg == (void*)&(msg->ping)) printf("PING\n");//0
			if ((int*)reg == &(msg->id)) printf("ID\n");//4
			if ((bool*)reg == &(msg->connection)) printf("CONNECTION\n");//8
			if ((float*)reg == &(msg->dirX)) printf("DIR X\n");//12
			if ((float*)reg == &(msg->dirY)) printf("DIR Y\n");//16
			if ((float*)reg == &(msg->posX)) printf("POS X\n");//20
			if ((float*)reg == &(msg->posY)) printf("POS Y\n");//24

		printf("%d: %x\n",i,*reg);
	}
	printf("\n");
}


int main(){
	printf("sizeof in_message es %lu, sizeof out_message es %lu\n",sizeof(in_message_t),sizeof(out_message_t));
	printf("sizeof char es %lu\n",sizeof(char));
	
	out_message_t test = {.ping = 0, .id=0, .connection = true, .dirX = 1.0 , .dirY = -1.0,
							.posX = 2.0, .posY = 3.0};

	hexdump_outmsg(&test);

	return 0;
}
