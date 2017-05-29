#include "Jefe.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 70
#define HEIGHT 50

#define BOSS_MOV_SPAN 250		//calcular junto con la bola segun la pantalla
#define BOSS_MOV_SPEED 0.2		//cuanto se mueve por vez


//Si se quiere se le puede agregar que suba y baje un poco, pero va a ser fruta..
//.. el movimiento de la bola!
void Jefe::mover(){//draft, faltan frames
	if (contador_mov > BOSS_MOV_SPAN){
		contador_mov = 0;
		direccion = (-1)*direccion;
	}
	contador_mov++;
	x+= direccion*BOSS_MOV_SPEED;
}
