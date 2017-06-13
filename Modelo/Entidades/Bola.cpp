#include "Bola.hpp"
#include "../Player.hpp"
#include <stdio.h>

#define WIDTH 150
#define HEIGHT 150

//SE CALCULA RESPECTO DEL CENTRO DE LA BOLA, DESPUES AGREGAR PARA QUE SEA EL PUNTO QUE SE QUIERE
//RECORDAR SE USA r=200, sino calcular de vuelta!
//VAN A SER 3 PUNTOS PRINCIPALES (izq, medio, der) y 2* INTERMEDIOS
//EN ESTA IMPL SON 5 INTERMEDIOS, SI ANDA MUY LENTO PONER MENOS
//LISTA DE ANGULOS ENTONCES:
//	-90		-75		-60		-45		-30		-15		0	+15		+30	   +45	    +60		+75		+90	
static float Xs[]={//X(t) = 200*cos(90-t)
/*
	-200.0,

	-200.0,	-193.18,	-173.2,	-141.42,	-100.0,	-51.78,	0.0, 51.78,	100.0, 141.42, 173.2,	193.18,	200.0,

	200.0
*/
-200.0

//	-90		-82.5	-75		-67.5	-60		etc	
	-200.0,	-198.3,	-193.2,	-184.78, -173.2, -158.67, -141.42, -121.75,	-100.0,	-76.54,	-51.76,	-26.1,	0.0,
//
	26.1,	51.76,	76.54,	100.0,	 121.75, 141.42,   158.67,   173.2,	184.78, 193.2,	198.3,	200.0,

200.0

};
//Por ahora estamos trabajando con len(Xs)=len(Ys)=15
#define LARGO_X_Y 27
#define FACTOR_MOVIMIENTO_BOLA 30
//Los extra del principio y final están ahi para que parezca que frena un toque, lo va a hacer..
//.. como 4 veces porque va y viene
static float Ys[]={//Y(t) = 200*sen(90-t)
/*
		0.0,
	
	   0.0,	 51.78,	 100.0,	 141.42,	 173.2,	 193.18, 200.0,193.18,	173.2, 141.42, 100.0,	51.78,	0.0,

		0.0
*/
	
0.0,
//	-90		-82.5	-75		-67.5	-60		etc	
	0.0,	26.11,	51.76,	76.54,	100.0,	121.75,	141.42,	158.67,	173.21,	184.78,	193.19,	198.29,	200.0,
//
	198.29,	193.19,	184.78,	173.21,	158.67,	141.42,	121.75,	100.0,	76.54,	51.76,	26.11,	0.0,

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
		if (contador_mov >= LARGO_X_Y*FACTOR_MOVIMIENTO_BOLA){
			direccion=false;
			contador_mov = LARGO_X_Y*FACTOR_MOVIMIENTO_BOLA -1;
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

	//iguanito que pinche
	jugador->recibirGolpe();
	jugador->lastimar();
}

out_message_t* Bola::getOutMessage(){
	return this->Entidad::getOutMessage(BALL_UPDATE);
}
out_message_t* Bola::getInitMessage(){
	return this->Entidad::getOutMessage(BALL_SET);
}
