#include "Pinche.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 200
#define HEIGHT 40

using namespace std;

Pinche::Pinche(float x, float y) : Entidad(x,y,WIDTH,HEIGHT){}

void Pinche::afectarA(Player* jugador){
	printf("monedas antes: %d\n", jugador->getMonedas());
	printf("vidas antes: %d\n", jugador->getVidas());
	jugador->recibirGolpe();
	printf("monedas despues: %d\n", jugador->getMonedas());
	printf("vidas despues: %d\n\n", jugador->getVidas());
}

out_message_t* Pinche::getOutMessage(){
	out_message_t* state = new out_message_t;
	return state;
}