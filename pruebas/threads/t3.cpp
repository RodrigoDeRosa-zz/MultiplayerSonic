#include <stdio.h>
#include <iostream>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

using namespace std;
#define LIMITE 1000

std::mutex n_mutex;

void safe_inc(int* n){
	//cout << "Arranca thread de ID:" << this_thread::get_id() << "con n=" << *n << endl;
	n_mutex.lock();
	while(*n < LIMITE){
		(*n)+=1;
	}
	n_mutex.unlock();
}


int main(){
	//A diferencia de t2.cpp, como este hace locks siempre el thread t1 va a completar el ciclo y el resto no va a poder hacer nada porque esta bloqueado n.
	//Este loop va a ser infinito porque nunca va a cumplirse a>LIMITE, por lo mismo de antes.
	//En t4.cpp se va a usar un if para ver que se llaman a distintos threads y nunca termina en >1000.
	int a;
	unsigned long long int cont=0;
	
	do{
	a = 0;
	thread t1(safe_inc,&a);
	thread t2(safe_inc,&a);//los thread arrancan ni bien se crean
	thread t3(safe_inc,&a);
	thread t4(safe_inc,&a);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cont++;
	if (cont > 1<<20){
		printf("van 2^20 corridas. Se resetea el contador.\n");
		cont=0;}
	}while((a<=LIMITE));	
	printf("Al final a vale: %d\n",a);
	printf("Numero de corridas: %lld\n",cont);
	return 0;
}
