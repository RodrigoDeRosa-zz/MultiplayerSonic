#include "Moneda.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 50
#define HEIGHT 50

using namespace std;

Moneda::Moneda(float x, float y) : Entidad(x,y,WIDTH,HEIGHT){}

void Moneda::afectarA(Player* jugador){
	printf("monedas antes: %d\n", jugador->getMonedas());
	jugador->agregarMonedas(1);
	printf("monedas antes: %d\n\n", jugador->getMonedas());
	//destruir moneda
}

out_message_t* Moneda::getOutMessage(){
	out_message_t* state = new out_message_t;
	return state;
}