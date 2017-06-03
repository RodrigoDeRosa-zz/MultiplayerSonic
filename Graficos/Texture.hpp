#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

class Texture{
    SDL_Texture* getTexture();
    SDL_Texture* texture;
    int width, height;
    Uint8 keyR, keyG, keyB;
    public:
        Texture();
        ~Texture();
        /*Carga una textura desde la direccion recibida en el string*/
        bool loadFromFile(string);
        //Crea una imagen a partir de un string de una fuente
        bool loadFromRenderedText(TTF_Font* font, string textureText, SDL_Color textColor);
        /*Libera la textura cargada*/
        void free();
        /*Define el color de transparencia de la superficie*/
        void setKeyColor(Uint8 r, Uint8 g, Uint8 b);
        //Setea un multiplicador de color para la textura
        void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b);
        /*Renderiza en la posicion dada por (x,y), usando el SDL_Rect como clipper*/
        void render(int x, int y, SDL_Rect* clip);
        void renderNoFill(int x, int y, SDL_Rect* clip);
        void renderWithMovement(int x, int y, SDL_Rect* clip);
        int getWidth();
        int getHeight();
        void setDimensions(int w, int h);
        bool operator==(Texture& other) const;
        void setColorMod();
        void setColorMod(Uint8 r, Uint8 g, Uint8 b);
};

#endif /*TEXTURE_HPP*/
