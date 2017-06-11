#include "Pinche.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 100
#define HEIGHT 47

using namespace std;

Pinche::Pinche(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Pinche::afectarA(Player* jugador){

	jugador->recibirGolpe();
	jugador->lastimar();
	
}

out_message_t* Pinche::getOutMessage(){
	return this->Entidad::getOutMessage(SPIKE_SET);
}

out_message_t* Pinche::getInitMessage(){
	return this->Entidad::getOutMessage(SPIKE_SET);
}
