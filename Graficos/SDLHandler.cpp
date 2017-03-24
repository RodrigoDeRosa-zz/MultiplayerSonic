#include "SDLHandler.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDLHandler::SDLHandler(){}
SDLHandler::~SDLHandler(){}

SDLHandler& SDLHandler::getInstance(){
    static SDLHandler instance;
    return instance;
}

bool SDLHandler::init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("ERROR: SDL could not initialize! SDL Error: %s", SDL_GetError());
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        printf("ERROR: SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
        SDL_Quit();//Se cierra el SDL originalmente inicializado
        return false;
    }
    return true;
}

void SDLHandler::close(){
    SDL_Quit();
    IMG_Quit();
}
