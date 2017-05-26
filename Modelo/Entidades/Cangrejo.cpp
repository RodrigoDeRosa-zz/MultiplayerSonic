#include "Cangrejo.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50

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

void Cangrejo::mover(){} //reescribir