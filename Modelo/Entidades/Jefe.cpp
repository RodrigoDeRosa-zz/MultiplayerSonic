#include "Jefe.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 239
#define HEIGHT 170	//TODO era 200 pero creo que anda mejor asi

#define BOSS_MOV_SPAN 2500		//calcular junto con la bola segun la pantalla
#define BOSS_MOV_SPEED 0.2		//cuanto se mueve por vez

#define BOSS_FRAME_FACTOR 20
#define BOSS_CANT_FRAMES 12

#define THRESHOLD_DESDE_ABAJO 10	//para ver que le pegue desde el costado y no desde abajo
#define SAFETY_DIST	5
//Si se quiere se le puede agregar que suba y baje un poco, pero va a ser fruta..
//.. el movimiento de la bola!
void Jefe::mover(){//draft, faltan frames
	if (contador_mov > BOSS_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
		moveActual = (moveActual==BOSSR ? BOSSL : BOSSR);
	}
	frame = (contador_mov / BOSS_FRAME_FACTOR) % BOSS_CANT_FRAMES;
	contador_mov++;
	x+= direccion*BOSS_MOV_SPEED;
}

void Jefe::afectarA(Player* jugador){
	//como esto vuela, puedo asumir que si lo toca esta atacando
	this->recibirDanio();

	//ahora hace tipo piedra para que no lo traspase
	//SOLO POR POSICION
	if(jugador->getBordeArriba() < (this->Entidad::getBordeAbajo() - THRESHOLD_DESDE_ABAJO)){
		//le estaba pegando desde un costado	
		float posicion;
		if(jugador->getX() < (this->Entidad::getBordeIzq()+WIDTH/2)){
			//entro desde la izquierda
			posicion = this->Entidad::getBordeIzq() - (jugador->getBordeDer() - jugador->getBordeIzq()) - SAFETY_DIST;		
		}
		else{
			//entro desde la derecha
			posicion = this->Entidad::getBordeDer()+SAFETY_DIST;
		}
		jugador->setX(posicion);
		//jugador->setCayendo();//TODO chequear si hace falta
	}
	else{
		//le estaba pegando desde abajo
		jugador->setCayendo();
		jugador->setY(this->Entidad::getBordeAbajo()+SAFETY_DIST);
	}
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

Jefe::Jefe(int id, float x, float y): Entidad(0,x,y,WIDTH,HEIGHT){}

out_message_t* Jefe::getOutMessage(){
	return this->Entidad::getOutMessage(BOSS_UPDATE);
}

out_message_t* Jefe::getInitMessage(){
	return this->Entidad::getOutMessage(BOSS_SET);
}

void Jefe::getAnclaje(float* targetX, float* targetY){
	*targetX = this->x + WIDTH/2.0;
 	*targetY = this->y + HEIGHT/4.0*3.0;
}
