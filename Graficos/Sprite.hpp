#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Texture.hpp"
#include <SDL2/SDL.h>

class Sprite{
    Texture* get_texture();
    protected:
        Texture* texture;
        SDL_Rect rectangle;
        int originX, originY, width, height;
        Uint8 red, green, blue;
    public:
        Sprite(int x, int y, int w, int h);
        ~Sprite();
        void update();
        /*Dibuja el sprite en pantalla*/
        void render();
        /*Define la textura del sprite*/
        void setTexture(Texture*);
        /*Define el color predeterminado del sprite en caso de falta de textura*/
        void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
        bool operator==(Sprite& other) const;
        Texture* getTexture();
};

#endif /*SPRITE_HPP*/
