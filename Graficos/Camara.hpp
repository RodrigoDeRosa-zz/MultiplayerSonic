#ifndef CAMARA_H_
#define CAMARA_H_

#include "Apuntado.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//class Apuntado;

class camara{
private:
	//camara
	SDL_Rect cam;
	//Velocidad fija en la que se mueve la camara
	int vel;
	//Velocidades para manejar el movimiento de la camara
	int velX;
	int velY;
	//Dimensiones de la camara
	int ancho;
	int alto;
	//Dimensiones del escenario
	int ancho_escenario;
	int alto_escenario;
	//Sprite al que sigue la camara
	Apuntado* apuntado;

public:
	camara(int posX_c,int posY_c,int vel_c, int ancho_c, int alto_c, int ancho_es, int alto_es);
	void moveCamara();

	/*getters*/
	SDL_Rect getCamara();
	int getX();
	int getY();

	//Operaciones apuntado
	void setApuntado( Apuntado* apun);
	void moveApuntado(int x, int y);
	void setEventApuntado( SDL_Event& e );

	void render();
};

#endif /* CAMARA_H_ */
