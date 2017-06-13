#include "Pez.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 39
#define HEIGHT 60


#define FISH_MOV_SPAN 600		//cuantas veces se mueve para un lado
#define FISH_MOV_SPEED 0.9		//cuanto se mueve por vez

#define FISH_FRAME_FACTOR	60
#define FISH_CANT_FRAMES	4

#define NO_DRAW_Y	2000
#define FISH_ADJUST 200

using namespace std;

Pez::Pez(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){
	oldY=y;
}

void Pez::afectarA(Player* jugador){
	if(jugador->estaAtacando() || !(jugador->recibirGolpe())){
		this->destruida = true;
		//sumar puntos a jugador
	}
}

out_message_t* Pez::getOutMessage(){
	return this->Entidad::getOutMessage(FISH_UPDATE);
}

out_message_t* Pez::getInitMessage(){
	return this->Entidad::getOutMessage(FISH_SET);
}

void Pez::mover(){//draft, faltan frames
	if (contador_mov > FISH_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
		frame = 0;
	}
	if (direccion > 0.0) moveActual = FISHD;
	else moveActual = FISHU;
	frame = (contador_mov/FISH_FRAME_FACTOR) % FISH_CANT_FRAMES;
	contador_mov++;
	if ((contador_mov < (CONT_INICIAL-FISH_ADJUST) && direccion < 0) || (contador_mov > (FISH_MOV_SPAN - CONT_INICIAL+FISH_ADJUST) && direccion > 0)){//ajustar este numero para que llegue al borde de la pantalla
		y = NO_DRAW_Y;
	}
	else{
		y = oldY;
		y+= direccion*FISH_MOV_SPEED;
		oldY=y;
	}
}
