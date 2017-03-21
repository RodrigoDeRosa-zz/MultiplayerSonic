#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Layer.hpp"
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void close(){
    IMG_Quit();
    SDL_Quit();
}

void init(SDL_Window* window, SDL_Renderer* renderer){
	SDL_Init( SDL_INIT_VIDEO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	window = SDL_CreateWindow( "WindowTests", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    IMG_Init( IMG_INIT_PNG );
}

int main(int argc, char** argv){
    SDL_Window* window;
    SDL_Renderer* renderer;

    init(window, renderer);

    Layer capa;
    capa.setImagePath("background.png");
    capa.load(renderer);

    bool running = true;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) running = false;
        }
        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        capa.draw(renderer);
        //Update screen
        SDL_RenderPresent(renderer);
        break;
    }
    close();
    return 0;
}
