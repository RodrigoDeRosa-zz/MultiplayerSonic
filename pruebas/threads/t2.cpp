#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;
#define LIMITE 1000
void nsafe_inc(int* n){
	cout << "Arranca thread de ID:" << this_thread::get_id() << "con n=" << *n << endl;
	//La linea de arriba se puede comentar para ver que arrancan con frula
	while(*n < LIMITE){
		(*n)+=1;
	}
}


int main(){
	//Se supone que al final del loop a == LIMITE
	//Se muestra como un incremento sin locking puede llevar a que al final de todo a != LIMITE
	//Se ve tambien que es no-deterministico: la cantidad de runs hasta que falla puede variar..
	//..osea que no es algo medible, es random.
	int a;
	long long cont=0;
	do{
	a = 0;
	thread t1(nsafe_inc,&a);
	thread t2(nsafe_inc,&a);//los thread arrancan ni bien se crean
	thread t3(nsafe_inc,&a);
	thread t4(nsafe_inc,&a);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cont++;
	}while(a<=LIMITE);	
	printf("Al final a vale: %d\n",a);
	printf("Numero de corridas: %lld\n",cont);
	return 0;
}
