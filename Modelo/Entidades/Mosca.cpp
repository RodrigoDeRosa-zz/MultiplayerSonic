#include "Mosca.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50

#define FLY_MOV_SPAN 250		//cuantas veces se mueve para un lado
#define FLY_MOV_SPEED 0.4		//cuanto se mueve por vez

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
	}
	contador_mov++;
	x+= direccion*FLY_MOV_SPEED;
}
