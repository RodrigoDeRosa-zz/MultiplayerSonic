#ifndef LAYER_HPP
#define LAYER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>
#include "SpriteGroup.hpp"
using namespace std;

class Layer{
    private:
        char id;
        char zIndex;
        string imagePath;
        SpriteGroup* sprites;
    public:
        Layer(); //Constructor
        ~Layer(); //Destructor
        /*Define el identificador de la capa*/
        void setId(char);
        /*Define el z-index de la capa*/
        void setZIndex(char);
        /*Define la direccion de la imagen de fondo de la capa*/
        void setImagePath(string);
        /*Si es una capa con imagen de fondo, carga la imagen en la direccion
        del path del objeto.*/
        void loadBackground(SDL_Renderer*);
        /*Agrega un sprite a la capa*/
        void addElement(Sprite*);
        /*Se dibujan todos los elementos de la capa en pantalla*/
        void draw(SDL_Renderer*);
        /*Libera los elementos de la capa*/
        void freeElements(void);
};

#endif //LAYER_HPP
