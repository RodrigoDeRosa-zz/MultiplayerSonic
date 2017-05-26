#include "Mosca.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50

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

void Mosca::mover(){} //reescribir