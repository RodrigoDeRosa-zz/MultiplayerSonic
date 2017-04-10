#include <stdio.h>
#include <iostream>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

using namespace std;
#define LIMITE 100

std::mutex n_mutex;

void safe_inc(int* n){
	cout << "Arranca thread de ID:" << this_thread::get_id() << "con n=" << *n << endl;
	n_mutex.lock();
	if(*n < LIMITE){
		(*n)+=1;
	}
	n_mutex.unlock();
}


int main(){
	//Se usan if en vez de while, todos van a poder agarrar su parte pero nadie va a agarrarlo con LIMITE y dejarlo en LIMITE+1
	//Como en cada iteracion se suman exactamente 4 y no puede terminar ningun thread hasta sumar su parte, siempre van a ser 25 iteraciones y siempre va a sumar 1000.
	//PODRIA LLEGAR A DAR DISTINTO si en vez de lock y join se usara try_lock o no se joineara, por lo que main no tendria que esperar a que todos hagan su parte y podria irse a la mierda antes, o llamar a alguien, chequear y que luego el otro sume. Esto tambien se arreglaria lockeando antes de chequear en el while.
	//!!!: si se cambia a <= el chequeo se hace un loop infinito como el de t3, porque nunca falla.
	int a;
	unsigned long long int cont=0;
	a = 0;
	do{
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
	}while((a<LIMITE));	
	printf("Al final a vale: %d\n",a);
	printf("Numero de corridas: %lld\n",cont);
	return 0;
}
