#ifndef CAMARA_H_
#define CAMARA_H_

#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class Sprite;

class camara{
private:
	//camara
	SDL_Rect cam;
	//posicion del vertice superior izquierdo
	int posX;
	int posY;
	//Velocidad fija en la que se mueve la camara
	int vel;
	//Velocidades para manejar el movimiento de la camara
	int velX;
	int velY;
	//Dimensiones de la camara
	int ancho;
	int alto;

public:
	camara(int posX_c,int posY_c,int vel_c, int ancho_c, int alto_c);
	void moveCamara(Sprite* sprite);
	SDL_Rect getCamara();
	int getX();
	int getY();
 
};

#endif /* CAMARA_H_ */