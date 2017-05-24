#include "Pinche.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 200
#define HEIGHT 40
/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 5

using namespace std;

Pinche::Pinche(float x, float y) : Entidad(x,y,WIDTH,HEIGHT){}

void Pinche::afectarA(Player* jugador){
	jugador->recibirGolpe();
}

out_message_t* Pinche::getOutMessage(){
	out_message_t* state = new out_message_t;
	return state;
}