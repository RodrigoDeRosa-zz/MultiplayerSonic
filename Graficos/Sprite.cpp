#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"

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
}

Sprite::~Sprite(){
    originX = 0;
    originY = 0;
    width = 0;
    height = 0;
    red = 0;
    green = 0;
    blue = 0;
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
