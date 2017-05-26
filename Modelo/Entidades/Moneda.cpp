#include "Moneda.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 50
#define HEIGHT 50

using namespace std;

Moneda::Moneda(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

void Moneda::afectarA(Player* jugador){
	jugador->agregarMonedas(1);
	//destruir moneda
}

out_message_t* Moneda::getOutMessage(){
	out_message_t* state = this->Entidad::getOutMessage(COIN_UPDATE);
	return state;
}

out_message_t* Moneda::getInitMessage(){
	return this->Entidad::getOutMessage(COIN_SET);
}