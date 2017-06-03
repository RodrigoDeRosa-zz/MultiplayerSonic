#include "SDLHandler.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../logger/current/Logger2.hpp"

#define SDLHANDLER_NONINITSDL_MSG "In SDLHandler::init(): SDL could not initialize! SDL Error: "
#define SDLHANDLER_NONINITIMG_MSG "In SDLHandler::init(): SDL_image could not initialize! SDL_image Error: "

SDLHandler::SDLHandler(){}
SDLHandler::~SDLHandler(){}

SDLHandler& SDLHandler::getInstance(){
    static SDLHandler instance;
    return instance;
}

bool SDLHandler::init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        Logger::getInstance().log(string(SDLHANDLER_NONINITSDL_MSG)+string(SDL_GetError()),BAJO);
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        Logger::getInstance().log(string(SDLHANDLER_NONINITIMG_MSG)+string(IMG_GetError()),BAJO);
        SDL_Quit();//Se cierra el SDL originalmente inicializado
        return false;
    }
    TTF_Init();
    return true;
}

void SDLHandler::close(){
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
