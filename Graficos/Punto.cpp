#include "Punto.hpp"
 
const int ANCHO_ESCENARIO = 1280;
const int ALTO_ESCENARIO = 960;

Punto::Punto(){
    inicializar();
    posX = 0;
    posY = 0;
	velX = 0;
    velY = 0;
}

void Punto::inicializar(){
    Texture* texturaPunto = new Texture();
    texturaPunto->loadFromFile("Graficos/dot.bmp");
}

void Punto::handleEvent( SDL_Event& e ){
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_UP: velY -= PUNTO_VEL; break;
            case SDLK_DOWN: velY += PUNTO_VEL; break;
            case SDLK_LEFT: velX -= PUNTO_VEL; break;
            case SDLK_RIGHT: velX += PUNTO_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: velY += PUNTO_VEL; break;
            case SDLK_DOWN: velY -= PUNTO_VEL; break;
            case SDLK_LEFT: velX += PUNTO_VEL; break;
            case SDLK_RIGHT: velX -= PUNTO_VEL; break;
        }
    }
}

void Punto::move(){
    posX += velX;

    if( ( posX < 0 ) || ( posX + ANCHO_PUNTO > ANCHO_ESCENARIO ) ){
        posX -= velX;
    }

    posY += velY;

    if( ( posY < 0 ) || ( posY + ALTO_PUNTO > ALTO_ESCENARIO ) ){
        posY -= velY;
    }
}

void Punto::render( int camX, int camY ){
	SDL_Rect* clip=NULL;
	//texturaPunto.render( posX - camX, posY - camY, clip);
}

int Punto::getPosX(){
	return posX;
}

int Punto::getPosY(){
	return posY;
}
