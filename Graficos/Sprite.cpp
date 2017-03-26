#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"



const int ANCHO_ESCENARIO = 1280;
const int ALTO_ESCENARIO = 960;

Sprite::Sprite(int x, int y, int w, int h, string nombre){
    texture = NULL;
    originX = x;
    originY = y;
    width = w;
    height = h;
    rectangle = {x, y, w, h};
    red = 0;
    green = 0;
    blue = 0;
    velX = 0;
    velY = 0;
    velocidad = 10;
    id = nombre;
}

Sprite::~Sprite(){
    originX = 0;
    originY = 0;
    width = 0;
    height = 0;
    red = 0;
    green = 0;
    blue = 0;
    velX=0;
    velY=0;
    texture = NULL; //La textura no se borra porque puede usarse para otra cosa.

}

void Sprite::update(){
    //To be overriden by subclass
}

void Sprite::setTexture(Texture* newTex){
    texture = newTex;
}

void Sprite::render(){
    //Si no tiene textura cargada, pinta con el color de fondo.
        //SDL_Rect camara = &(cam -> getCamara());
    if(texture) texture->render(originX, originY, &rectangle);
    else{
        Renderer::getInstance().setDrawColor(red, green, blue, 1);
        Renderer::getInstance().fillRect(&rectangle);
    }
}

void Sprite::setBackgroundColor(Uint8 r, Uint8 g, Uint8 b){
    red = r; green = g; blue = b;
}

Texture* Sprite::getTexture(){
    return texture;
}

bool Sprite::operator==(Sprite& other) const{
    return (texture == other.getTexture());
}

void Sprite::handleEvent( SDL_Event& e ){
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

void Sprite::move(){
    originX += velX;

    if( ( originX < 0 ) || ( originX + width > ANCHO_ESCENARIO ) ){
        originX -= velX;
    }

    originY += velY;

    if( ( originY < 0 ) || ( originY + height > ALTO_ESCENARIO ) ){
        originY -= velY;
    }
}

string Sprite::getID(){
    return id;
}

int Sprite::getX(){
    return originX;
}

int Sprite::getY(){
    return originY;
}

int Sprite::getWidth(){
    return width;
}

int Sprite::getHeight(){
    return height;
}