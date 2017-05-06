#include "Camara.hpp"
#define AVANCE 10
Camara::Camara(float posX_c,float posY_c, float vel_c, float ancho_c, float alto_c, float ancho_es, float alto_es){
	vel= vel_c;
	velX= 0;
	velY= 0;
	ancho= ancho_c;
	alto= alto_c;
	ancho_escenario= ancho_es;
	alto_escenario=alto_es;
	cam = {posX_c,posY_c,ancho_c,alto_c};
}

void Camara::setPosicion(float posx, float posy){
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

float Camara::getX(){
	return cam.x;
}

float Camara::getY(){
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
