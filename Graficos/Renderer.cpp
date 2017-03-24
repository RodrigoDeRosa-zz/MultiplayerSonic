#include "Window.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL.h>

/*Constructor*/
Renderer::Renderer(){
    renderer = NULL;
}

/*Destructor*/
Renderer::~Renderer(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
}

/*Metodo de obtencion de una instancia del singleton*/
Renderer& Renderer::getInstance(){
    static Renderer instance;
    return instance;
}

/*Incializa el SDL_Renderer*/
bool Renderer::init(){
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
        printf("WARNING: Linear texture filtering not enabled!\n");
    }
    renderer = Window::getInstance().initRenderer();
    if(!renderer){
        printf("ERROR: Renderer could not be initialized!\n");
        return false;
    }
    setDrawColor(0x00, 0xFF, 0xFF, 0xFF);
}

/*Define el color de dibujado del renderer*/
void Renderer::setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    if(!renderer){
        printf("ERROR: No renderer to set color to!\n");
        return;
    }
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

/*Crea una textura desde la superficie recibida*/
SDL_Texture* Renderer::getTextureFromSurface(SDL_Surface* surface){
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/*Renderiza la parte de la textura recibida dada por clip donde indica el renderQuad*/
void Renderer::renderTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* renderQuad){
    SDL_RenderCopy(renderer, tex, clip, renderQuad);
}

/*Pinta el SDL_Rect recibido con el color de dibujado*/
void Renderer::fillRect(SDL_Rect* rect){
    SDL_RenderFillRect(renderer, rect);
}

void Renderer::clear(){
    SDL_RenderClear(renderer);
}

void Renderer::draw(){
    SDL_RenderPresent(renderer);
}
