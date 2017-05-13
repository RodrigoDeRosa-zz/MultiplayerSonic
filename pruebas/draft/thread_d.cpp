#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
//resto de includes


//LAS FUNCIONES QUE RECIBE EL PTHREAD SON VOID* -> VOID*
//Por lo general el arg suele ser un puntero a una estructura de datos que te interese, casteado a void*.
//Por ejemplo, un Server* lo casteas a void* y lo pasas como arg.
void* f_controller(void* arg);
void* f_model(void* arg);


//en otro thread mas habra que a imprimir la vista cada X tiempo, o tal vez no hace falta el f_model y eso se hace en el main


int main(){

	//asi se declaran
	pthread_t controller_thread;
	pthread_t model_thread;

	//asi se lanzan
	//recibe &thread, NULL, f(), arg
	//IMPORTANTE: la f llamada tiene que estar definida al mismo scope que main (==global), y no puede ser un método de una clase. Sí o sí es una funcion static como main.
	pthread_create(&controller_thread,NULL,f_controller,NULL);
	pthread_create(&model_thread,NULL,f_model,NULL);

	//a partir de aca ya estan andando ambos threads, no se sabe cuando ejecutan qué pero se sabe que estan andando!
	
	//asi se espera a que terminen
	//recibe el thread y un puntero a void* si se quiere guardar el valor del exit de thread.
	//si es NULL no lo guarda en ningun lado y listo.
	//IMPORTANTE: join NO termina la ejecucion de los threads, bloquea main hasta que el thread termine de la misma forma que fgets/scanf/gets bloquean hasta que les ingresas algo por teclado.
	//Como hacer que terminen los threads es un problema de la f() que te armaste (ver abajo)
	pthread_join(controller_thread,NULL);
	pthread_join(model_thread,NULL);

	//a partir de aca ya se que ambos threads terminaron!
	
	//ahora solo queda terminar el main

	return 0;
}

/* LAS FUNCIONES DEBEN SER DE UN ESTILO
	inicializacion
	while(condicion){
		el loop pseudo-infinito
	}
	finalizacion de la funcion
	return NULL

	Y DESDE AFUERA SE CONTROLA LA CONDICION PARA PODER CORTARLO
*/
void* f_controller(void* arg){
	si hace falta inicializar algo, hacerlo aca
	while (andando){
		if (no hay SDL event o como se llame apretar teclas){
			usleep(algo de tiempo porque si se hace el while sin nada se lagea todo);
			continue;
		} //este if solo hace falta si la funcion para obtener evento no es bloqueante
		
		//a partir de aca se que hay SDL event y de alguna forma lo obtuve
		key_event key = procesar SDL_event(evento);
		queueToSend(key);
	}
	//a partir de aca no esta andando el juego (andando==false)
	cerrar todo lo que haya que cerrar
	return NULL;
}

void* f_model(void* arg){
	si hace falta inicializar algo, hacerlo aca
	while(andando){
		if(queue de msgs entrantes==vacia){
			usleep por lo mismo que antes
			continue;
		}
		//a partir de aca se que hay eventos para desencolar
		while (queue de msgs no vacia){
			desencolar evento entrante			
			modificar estado del juego(evento)
		} 
	}
	//a partir de aca no esta andando el juego (andando==false)
	cerrar todo lo que haya que cerrar
	return NULL;
}


