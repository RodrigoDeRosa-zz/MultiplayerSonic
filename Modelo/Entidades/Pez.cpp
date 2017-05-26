#include "Pez.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 50
#define HEIGHT 100

using namespace std;

Pez::Pez(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Pez::afectarA(Player* jugador){
	if(jugador->estaAtacando()){
		this->destruida = true;
		//sumar puntos a jugador
	}
	else jugador->recibirGolpe();
}

out_message_t* Pez::getOutMessage(){
	return this->Entidad::getOutMessage(FISH_UPDATE);
}

out_message_t* Pez::getInitMessage(){
	return this->Entidad::getOutMessage(FISH_SET);
}

void Pez::mover(){} //reescribir