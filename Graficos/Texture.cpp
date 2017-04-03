#include "Texture.hpp"
#include "Renderer.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logger2.hpp"
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

bool Texture::loadFromFile(string path){
    //Se libera la textura preexistente si es que existia
    free();
    //Textura final
    SDL_Texture* newTex = NULL;
    //Carga la imagen de la direccion indicada
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(!loadedSurface){
        //printf("ERROR: Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError() );
       	Logger::getInstance().log(string(TEXTURE_LOADFILE_MSG) + path + string(". SDL_Image Error: ") + string(IMG_GetError()));
	return false;
    }else{
        //Se le pasa el color utilizado como key a la superficie
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyR, keyB, keyG));

        //Se crea la textura a partir de los pixeles de la superficie
        newTex = Renderer::getInstance().getTextureFromSurface(loadedSurface);
        if(!newTex){
            //printf("ERROR: Unable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError());
	    Logger::getInstance().log(string(TEXTURE_CREATETEXTURE_MSG) + path + string(". SDL_Image Error: ") + string(SDL_GetError()));
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
