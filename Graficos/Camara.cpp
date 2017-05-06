#include "Camara.hpp"
#define AVANCE 10
Camara::Camara(int posX_c,int posY_c, int vel_c, int ancho_c, int alto_c, int ancho_es, int alto_es){
	vel= vel_c;
	velX= 0;
	velY= 0;
	ancho= ancho_c;
	alto= alto_c;
	ancho_escenario= ancho_es;
	alto_escenario=alto_es;
	cam = {posX_c,posY_c,ancho_c,alto_c};
}

void Camara::setPosicion(int posx, int posy){
	cam.x = posx;
	cam.y = posy;
}

void Camara::moveCamara(bool direccion){
	/*Recibe un bool que es true si se mueve para la derecha
	o false si se mueve para la izquierda*/

	if (direccion){
		cam.x += AVANCE;
	}
	else{
		cam.x -= AVANCE;
	}

	if( cam.x < 0 ){
		cam.x = 0;}

	if( cam.y < 0 ){
		cam.y = 0;}

	if( cam.x > ancho_escenario - cam.w ){
		cam.x = ancho_escenario - cam.w;}

	if( cam.y > alto_escenario -cam.h ){
		cam.y = alto_escenario - cam.h;}
}

void Camara::render(){
	apuntado->render(this);
}

SDL_Rect Camara::getCamara(){
	return cam;
}

int Camara::getX(){
	return cam.x;
}

int Camara::getY(){
	return cam.y;
}

// void Camara::setEventApuntado( SDL_Event& e ){
// 	apuntado->handleEvent(e);
// }
// void Camara::moveApuntado(){
// 	apuntado->move(ancho_escenario, alto_escenario);
// }
// void Camara::setApuntado(Apuntado* apun){
// 		apuntado = apun;
// }
