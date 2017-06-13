#include "Bola.hpp"
#include "../Player.hpp"
#include <stdio.h>

#define WIDTH 150
#define HEIGHT 150

//SE CALCULA RESPECTO DEL CENTRO DE LA BOLA, DESPUES AGREGAR PARA QUE SEA EL PUNTO QUE SE QUIERE
//RECORDAR SE USA r=100, sino calcular de vuelta!
//VAN A SER 3 PUNTOS PRINCIPALES (izq, medio, der) y 2* INTERMEDIOS
//EN ESTA IMPL SON 5 INTERMEDIOS, SI ANDA MUY LENTO PONER MENOS
//LISTA DE ANGULOS ENTONCES:
//	-90		-75		-60		-45		-30		-15		0	+15		+30	   +45	    +60		+75		+90	
static float Xs[]={
	-200.0,

	-200.0,	-193.18,	-173.2,	-141.42,	-100.0,	-51.78,	0.0, 51.78,	100.0, 141.42, 173.2,	193.18,	200.0,

	200.0
};
//Por ahora estamos trabajando con len(Xs)=len(Ys)=15
#define LARGO_X_Y 15
#define FACTOR_MOVIMIENTO_BOLA 4
//Los extra del principio y final están ahi para que parezca que frena un toque, lo va a hacer..
//.. como 4 veces porque va y viene
static float Ys[]={
		0.0,
	
	   0.0,	 51.78,	 100.0,	 141.42,	 173.2,	 193.18, 200.0,193.18,	173.2, 141.42, 100.0,	51.78,	0.0,

		0.0
};
void Bola::mover(){
	float jefeX,jefeY;
	jefe->getAnclaje(&jefeX,&jefeY);

	//muevo la bola segun contador actual
	this->x = jefeX + Xs[contador_mov/FACTOR_MOVIMIENTO_BOLA] - WIDTH/2;
	this->y = jefeY + Ys[contador_mov/FACTOR_MOVIMIENTO_BOLA] - HEIGHT/2;

	if (direccion){//si esta yendo hacia la derecha
		//incremento el contador
		contador_mov++;
		if (contador_mov >= LARGO_X_Y){
			direccion=false;
			contador_mov = LARGO_X_Y -1;
		}
	}
	else{//si esta yendo hacia la izquierda	
		contador_mov--;
		if (contador_mov < 0){
			direccion=true;
			contador_mov = 0;
		}
	}
}

Bola::Bola(int id, float x, float y, Jefe* j) : Entidad(0,x,y,WIDTH,HEIGHT){
	this->jefe = j;
}

void Bola::destruir(){
	this->destruida = true;
}

void Bola::afectarA(Player* jugador){
	//no importa si esta atacando esto lo lastima
	jugador->recibirGolpe();
	//TODO necesita tambien el lastimar?
}

out_message_t* Bola::getOutMessage(){
	return this->Entidad::getOutMessage(BALL_UPDATE);
}
out_message_t* Bola::getInitMessage(){
	return this->Entidad::getOutMessage(BALL_SET);
}
