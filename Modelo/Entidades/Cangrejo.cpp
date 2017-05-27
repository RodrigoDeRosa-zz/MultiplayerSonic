#include "Cangrejo.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50


#define CRAB_MOV_SPAN 300		//cuantas veces se mueve para un lado
#define CRAB_MOV_SPEED 0.2		//cuanto se mueve por vez

using namespace std;

Cangrejo::Cangrejo(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Cangrejo::afectarA(Player* jugador){
	if(jugador->estaAtacando()){
		this->destruida = true;
		//sumar puntos a jugador
	}
	else jugador->recibirGolpe();
}

out_message_t* Cangrejo::getOutMessage(){
	return this->Entidad::getOutMessage(CRAB_UPDATE);
}

out_message_t* Cangrejo::getInitMessage(){
	return this->Entidad::getOutMessage(CRAB_SET);
}

void Cangrejo::mover(){//draft, faltan frames
	if (contador_mov > CRAB_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
	}
	contador_mov++;
	x+= direccion*CRAB_MOV_SPEED;
} 
