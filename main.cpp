#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Sprites/Sprite.h"
#include "Sprites/SpriteGroup.h"
#include "controlGrafico/controlGrafico.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void control_framerate(Uint32 starting_tick) {
	
	if ((1000 / fps) > (SDL_GetTicks() - starting_tick)) {
		SDL_Delay((1000 / fps) - (SDL_GetTicks() - starting_tick));
	}

}

int main(int argc, char** argv){
	
	if( !init( window, renderer) ){
		//Levantar el error.
	}
	else{
		Sprite bloque() 
		
		Uint32 starting_tick;
		SDL_Event e;
		bool running = true;

		while (running) {

		starting_tick = SDL_GetTicks(); //lo utilizo para limitar los fps

			while (SDL_PollEvent(&e)) {

				//cerrado de ventana
				if (e.type == SDL_QUIT) {
				running = false;
				break;
				}
				
				//Clear Screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				
				
				//Update screen
				SDL_RenderPresent( gRenderer );

				control_framerate(starting_tick);
			}
		}	
	close(window, renderer);
	return 0;	
}
