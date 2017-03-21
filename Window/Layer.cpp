#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>
#include "Layer.hpp"
#include "LTexture.hpp"
#include "Sprite.hpp"
#include "SpriteGroup.hpp"
using namespace std;

/*Constructor*/
Layer::Layer(){
    id = 0;
    zIndex = 0;
    imagePath = "";
    sprites = new SpriteGroup();
}
/*Destructor*/
Layer::~Layer(){
    id = 0;
    zIndex = 0;
    imagePath = "";
    freeElements();
}
/*Define el identificador de la capa*/
void Layer::setId(char i){
    id = i;
}
/*Define el valor del z-index de la capa*/
void Layer::setZIndex(char z){
    zIndex = z;
}
/*Define la direccion de la imagen de la capa*/
void Layer::setImagePath(string path){
    imagePath = path;
}
/*Si es una capa con imagen de fondo, carga la imagen en la direccion del path del objeto.*/
void Layer::loadBackground(SDL_Renderer* renderer){
    /*Se crea la textura con la imagen de fondo*/
    LTexture* tex = new LTexture();
    tex.loadFromFile(imagePath, renderer);
    /*Se crea el sprite con dicha textura*/
    Sprite* background = new Sprite();
    background.setTexture(tex);
    /*Se agrega el sptrite al conjunto de sprites de la capa*/
    sprites.add(background);
}
/*Agrega un sprite a la capa*/
void Layer::addElement(Sprite* sprite){
    sprites.add(sprite);
}
/*Se dibuja en pantalla*/
void Layer::draw(SDL_Renderer* renderer){
    sprites.draw(renderer);
}
/*Libera los elementos de la capa*/
void Layer::freeElements(){
    if (sprites){
        delete sprites;
        sprites = NULL;
    }
}
