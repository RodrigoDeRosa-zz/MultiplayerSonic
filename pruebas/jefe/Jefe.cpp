#include "Jefe.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50

#define BOSS_MOV_SPAN 250		//calcular junto con la bola segun la pantalla
#define BOSS_MOV_SPEED 0.2		//cuanto se mueve por vez


//Si se quiere se le puede agregar que suba y baje un poco, pero va a ser fruta..
//.. el movimiento de la bola!
void Jefe::mover(){//draft, faltan frames
	if (contador_mov > BOSS_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
	}
	contador_mov++;
	x+= direccion*BOSS_MOV_SPEED;
}

void Jefe::afectarA(Player* jugador){
	//como esto vuela, puedo asumir que si lo toca esta atacando
	this->recibirDanio();
}

void Jefe::recibirDanio(){
	this->vidas-=1;
	if (this->vidas > 0){
		//efecto de danio?
		return;
	}
	else{
		//efecto de morir?
		this->destruida = true;
	}
}

Jefe::Jefe(int id, float x, float y): Entidad(id,x,y,WIDTH,HEIGHT){}

out_message_t* Jefe::getOutMessage(){}//TODO

out_message_t* Jefe::getInitMessage(){}//TODO

