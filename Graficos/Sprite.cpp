#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"

int velocidad = 1;

Sprite::Sprite(int x, int y, int w, int h){
    texture = NULL;
    originX = x;
    originY = y;
    width = w;
    height = h;
    rectangle = {x, y, w, h};
    red = 0;
    green = 0;
    blue = 0;
    zIndex = 0;
}

Sprite::~Sprite(){
    originX = 0;
    originY = 0;
    width = 0;
    height = 0;
    red = 0;
    green = 0;
    blue = 0;
    zIndex = 0;

    if (texture) texture = NULL; //La textura no se borra porque puede usarse para otra cosa.
}

void Sprite::update(){
    //To be overriden by subclass
}

void Sprite::setTexture(Texture* newTex){
    texture = newTex;
}

void Sprite::render(camara* cam){
    //Si no tiene textura cargada, pinta con el color de fondo.
    int auxX = originX - cam->getX();
    int auxY = originY - cam->getY();
    Renderer::getInstance().setDrawColor(red, green, blue, 1);

    if(texture) texture->render(auxX, auxY, &rectangle);
        else{
        	int aux1 = rectangle.x;
        	int aux2 = rectangle.y;

            rectangle.x -= cam->getX();
            rectangle.y -= cam->getY();

            Renderer::getInstance().fillRect(&rectangle);

            rectangle.x = aux1;
            rectangle.y = aux2;
        }
    }

void Sprite::render(int x, int y, camara* cam){
    //renderiza las texturas de fondo.
    SDL_Rect camara = cam -> getCamara();
    int X = originX - cam->getX();
    int Y = originX - cam->getY();
    if(texture) texture->render(X, Y, &rectangle);
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

void Sprite::setIndexZ(int index){
        zIndex = index;
}

int Sprite::getZIndex(){
    return zIndex;
}

bool Sprite::operator<(Sprite& other) const{
    return (zIndex < other.getZIndex());
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
