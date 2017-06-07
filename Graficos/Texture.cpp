#include "Texture.hpp"
#include "Renderer.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../logger/current/Logger2.hpp"
using namespace std;

#define TEXTURE_LOADFILE_MSG "In Texture::loadFromFile(): Unable to load image "
#define TEXTURE_CREATETEXTURE_MSG "In Texture::loadFromFile(): Unable to create texture from "

Texture::Texture(){
    texture = NULL;
    width = 0;
    height = 0;
    keyR = 0x0;
    keyG = 0xFF;
    keyB = 0xFF;
}

Texture::~Texture(){
    free();
}

void Texture::free(){
    //Libera la textura si existe
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

/*Define el color de transparencia de la superficie*/
void Texture::setKeyColor(Uint8 r, Uint8 g, Uint8 b){
    keyR = r; keyG = g; keyB = b;
}

//Multiplica la texturea por el color pasado en RGB
void Texture::setBackgroundColor(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod(texture, r, g, b);
}


bool Texture::loadFromFile(string path){
    //Se libera la textura preexistente si es que existia
    free();
    //Textura final
    SDL_Texture* newTex = NULL;
    //Carga la imagen de la direccion indicada
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface){
       	Logger::getInstance().log(string(TEXTURE_LOADFILE_MSG) + path + string(". SDL_Image Error: ") + string(IMG_GetError()),MEDIO);
	    return false;
    }else{
        //Se le pasa el color utilizado como key a la superficie
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyR, keyB, keyG));

        //Se crea la textura a partir de los pixeles de la superficie
        newTex = Renderer::getInstance().getTextureFromSurface(loadedSurface);
        if(!newTex){
	        Logger::getInstance().log(string(TEXTURE_CREATETEXTURE_MSG) + path + string(". SDL_Image Error: ") + string(SDL_GetError()),MEDIO);
            /*Libera la superficie cargada de la imagen.*/
            SDL_FreeSurface(loadedSurface);
            return false;
        }else{
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        /*Libera la superficie cargada de la imagen*/
        SDL_FreeSurface(loadedSurface);
    }
    texture = newTex;
    return texture != NULL;
}

/*Creador de textura a partir de texto*/
bool Texture::loadFromRenderedText(TTF_Font* font, string textureText, SDL_Color textColor){
    //Libera la textura anterior
    free();
    //Renderiza el texto
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (!textSurface){
        printf("Surface is NULL, TTF_ERROR: %s\n", TTF_GetError());
        return false;
    }
    //Crea la textura a partir de los pixeles de la superficie
    SDL_Texture* newTex = Renderer::getInstance().getTextureFromSurface(textSurface);
    //Setea las dimensiones a partir de la superficie
    width = textSurface->w;
    height = textSurface->h;
    texture = newTex;
    //Libera la superficie
    SDL_FreeSurface(textSurface);

    return texture != NULL;
}

/*Renderiza en la posicion dada por (x,y), usando el SDL_Rect como clipper*/
void Texture::render(int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = {x, y, width, height};
    if (clip){
        if (width < clip->w){
            SDL_Rect fillRect = {x + clip->w, y, width - clip->w, clip->h};
            Renderer::getInstance().fillRect(&fillRect);
        } else renderQuad.w = clip->w;
        if (height < clip->h){
            SDL_Rect fillRect = {x, y + clip->h, clip->w, height - clip->h};
            Renderer::getInstance().fillRect(&fillRect);
        } else renderQuad.h = clip->h;
    }
    int auxX = clip->x;
    int auxY = clip->y;
    clip->x = 0;
    clip->y = 0;
    Renderer::getInstance().renderTexture(texture, clip, &renderQuad);
    clip->x = auxX;
    clip->y = auxY;
}

void Texture::renderNoFill(int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = {x, y, width, height};
    int auxX = clip->x;
    int auxY = clip->y;
    clip->x = 0;
    clip->y = 0;
    Renderer::getInstance().renderTexture(texture, clip, &renderQuad);
    clip->x = auxX;
    clip->y = auxY;
}

/*Renderiza en la posicion dada por (x,y), sin mantener la coord. x e y de el SDL_Rect*/
void Texture::renderWithMovement(int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = {x, y, width, height};
    if (clip){
        if (width < clip->w){
            SDL_Rect fillRect = {x + clip->w, y, width - clip->w, clip->h};
            Renderer::getInstance().fillRect(&fillRect);
        } else renderQuad.w = clip->w;
        if (height < clip->h){

            SDL_Rect fillRect = {x, y + clip->h, clip->w, height - clip->h};
            Renderer::getInstance().fillRect(&fillRect);
        } else renderQuad.h = clip->h;
    }
    Renderer::getInstance().renderTexture(texture, clip, &renderQuad);
}

int Texture::getWidth(){
    return width;
}
int Texture::getHeight(){
    return height;
}

void Texture::setDimensions(int w, int h){
    width = w;
    height = h;
}


SDL_Texture* Texture::getTexture(){
    return texture;
}

bool Texture::operator==(Texture& other) const{
    return (texture == other.getTexture());
}

void Texture::setColorMod(){
    SDL_SetTextureColorMod(texture, keyR, keyG, keyB);
}

void Texture::setColorMod(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod(texture, r, g, b);
}
