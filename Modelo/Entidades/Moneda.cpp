#include "Moneda.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 40
#define HEIGHT 40

#define COIN_FRAME_FACTOR	60
#define COIN_CANT_FRAMES	4
using namespace std;

Moneda::Moneda(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Moneda::afectarA(Player* jugador){
	if(!(this->destruida))jugador->agregarMonedas(1);
	this->destruida = true;
	//destruir moneda
}

out_message_t* Moneda::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(COIN_UPDATE);
	return state;
}

out_message_t* Moneda::getInitMessage(){
	return this->Entidad::getOutMessage(COIN_SET);
}

void Moneda::mover(){//draft, faltan frames
	frame = (contador_mov/COIN_FRAME_FACTOR) % COIN_CANT_FRAMES;
	contador_mov++;
}
