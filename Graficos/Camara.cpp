#include "Camara.hpp"

camara::camara(int posX_c,int posY_c, int vel_c, int ancho_c, int alto_c, int ancho_es, int alto_es){
	vel= vel_c;
	velX= 0;
	velY= 0;
	ancho= ancho_c;
	alto= alto_c;
	ancho_escenario= ancho_es;
	alto_escenario=alto_es;
	cam= {posX_c,posY_c,ancho_c,alto_c};
}

void camara::moveCamara(Sprite* sprite){
	
	cam.x = ( sprite->getX() + (sprite->getWidth() / 2) ) - ancho / 2;
	cam.y = ( sprite->getY() + (sprite->getHeight() / 2) ) - alto / 2;

	if( cam.x < 0 ){
		cam.x = 0;
	}
	if( cam.y < 0 ){
		cam.y = 0;
	}
	if( cam.x > ancho_escenario - cam.w ){
		cam.x = ancho_escenario - cam.w;
	}
	if( cam.y > alto_escenario -cam.h ){
		cam.y = alto_escenario - cam.h;
	}
}

SDL_Rect camara::getCamara(){
	return cam;
}

int camara::getX(){
	return cam.x;
}

int camara::getY(){
	return cam.y;
}

