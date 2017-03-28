#include "Apuntado.hpp"

Apuntado::Apuntado(int x, int y, int w, int h, int vel_s) : Sprite(x,y,w,h){
    velX=0;
    velY=0;
    velocidad=vel_s;
}

void Apuntado::handleEvent( SDL_Event& e ){
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_UP: velY -= velocidad; break;
            case SDLK_DOWN: velY += velocidad; break;
            case SDLK_LEFT: velX -= velocidad; break;
            case SDLK_RIGHT: velX += velocidad; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_UP: velY += velocidad; break;
            case SDLK_DOWN: velY -= velocidad; break;
            case SDLK_LEFT: velX += velocidad; break;
            case SDLK_RIGHT: velX -= velocidad; break;
        }
    }
}

void Apuntado::move(int AnchoEscenario, int AltoEscenario){
    originX += velX;

    if( ( originX < 0 ) || ( originX + width > AnchoEscenario ) ){
        originX -= velX;
    }

    originY += velY;

    if( ( originY < 0 ) || ( originY + height > AltoEscenario ) ){
        originY -= velY;
    }
}
