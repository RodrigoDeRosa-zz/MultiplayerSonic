#include <stdio.h>
#include <iostream>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;

#define STR1 "hola"
#define STR2 "chau"
#define SLEEP_T 1	//[seg]
void printear(string str){
	while(true){
		cout << str <<"\n";
		this_thread::sleep_for(chrono::seconds(SLEEP_T));
	}
}

int main(){
	thread t1(printear,string(STR1));
	thread t2(printear,string(STR2));//los thread arrancan ni bien se crean
	t1.join();
	t2.join();	//si no hubiera joins y el main termina hace terminate a los otros thread..
			//..y como no tienen forma de atajarlo hay segfault
	return 0;
}
