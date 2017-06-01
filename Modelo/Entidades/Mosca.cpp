#include "Mosca.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 56
#define HEIGHT 60

#define FLY_MOV_SPAN 1000		//cuantas veces se mueve para un lado
#define FLY_MOV_SPEED 0.2		//cuanto se mueve por vez

#define FLY_FRAME_FACTOR 8
#define FLY_CANT_FRAMES	4
using namespace std;

Mosca::Mosca(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Mosca::afectarA(Player* jugador){
	if(jugador->estaAtacando()){
		this->destruida = true;
		//sumar puntos a jugador
	}
	else jugador->recibirGolpe();
}

out_message_t* Mosca::getOutMessage(){
	return this->Entidad::getOutMessage(FLY_UPDATE);
}

out_message_t* Mosca::getInitMessage(){
	return this->Entidad::getOutMessage(FLY_SET);
}

void Mosca::mover(){//draft, faltan frames
	if (contador_mov > FLY_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
		frame = 0;
	}
	if (direccion > 0.0) moveActual = FLYD;
	else moveActual = FLYL;
	frame = (contador_mov/FLY_FRAME_FACTOR) % FLY_CANT_FRAMES;
	contador_mov++;
	x+= direccion*FLY_MOV_SPEED;
}
