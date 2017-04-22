#ifndef SPRITE_HPP
#define SPRITE_HPP


#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Camara;

class Sprite{
    Texture* get_texture();
    protected:
        Texture* texture;
        SDL_Rect rectangle;
        float originX, originY;
        int width, height, zIndex;
        Uint8 red, green, blue;

    public:
        Sprite(float x, float y, int w, int h);
        ~Sprite();
        void update();
        /*Dibuja el sprite en pantalla*/
        virtual void render(Camara*);
        /*Dibuja las imagenes de fondo*/
        void render(int x, int y, Camara* cam);
        /*Define la textura del sprite*/
        void setTexture(Texture*);
        /*Define el color predeterminado del sprite en caso de falta de textura*/
        void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
        bool operator==(Sprite& other) const;
        bool operator<(Sprite& other) const;
        Texture* getTexture();
        int getZIndex();

        void setIndexZ(int);

        /*getters*/
        int getX();
        int getY();

        int getWidth();
        int getHeight();
};

#endif /*SPRITE_HPP*/
