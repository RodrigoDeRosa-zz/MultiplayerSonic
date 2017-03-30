#include "Apuntado.hpp"
//tiene que ser singleton

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
/*void Apuntado::render(int x, int y, camara* cam){
    //renderiza las texturas de fondo.
    SDL_Rect camara = cam -> getCamara();
    int X= originX - cam->getX();
    int Y = originX - cam->getY();
    if(texture){
      SDL_SetColorKey( superficieCargada, SDL_TRUE, SDL_MapRGB( superficieCargada->format, 0, 0xFF, 0xFF ));
      texture->render(X, Y, &rectangle);
    }
    else{
        Renderer::getInstance().setDrawColor(red, green, blue, 1);
        Renderer::getInstance().fillRect(&rectangle);
    }
}*/
