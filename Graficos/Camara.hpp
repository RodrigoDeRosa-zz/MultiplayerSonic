#ifndef CAMARA_H_
#define CAMARA_H_

#include "Apuntado.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class Camara{
private:
	//camara
	SDL_Rect cam;
	//Velocidad fija en la que se mueve la camara
	float vel;
	//Velocidades para manejar el movimiento de la camara
	float velX;
	float velY;
	//Dimensiones de la camara
	float ancho;
	float alto;
	//Dimensiones del escenario
	float ancho_escenario;
	float alto_escenario;
	//Sprite al que sigue la camara
	Apuntado* apuntado;

public:
	Camara(float posX_c,float posY_c,float vel_c, float ancho_c, float alto_c, float ancho_es, float alto_es);
	void moveCamara(bool);
	void setPosicion(float, float);

	/*getters*/
	SDL_Rect getCamara();
	float getX();
	float getY();

	void render();

	//Operaciones apuntado
	// void setApuntado( Apuntado* apun);
	// void moveApuntado();
	// void setEventApuntado( SDL_Event& e );
};

#endif /* CAMARA_H_ */
