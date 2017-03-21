#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Sprites/LTexture.hpp"
#include "Sprites/Sprite.hpp"
#include "Sprites/SpriteGroup.hpp"
#include "controlGrafico/controlGrafico.hpp"

#define fps 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
LTexture gBackgroundTexture;

void control_framerate(Uint32 starting_tick) {

	if ((1000 / fps) > (SDL_GetTicks() - starting_tick)) {
		SDL_Delay((1000 / fps) - (SDL_GetTicks() - starting_tick));
	}

}

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "background.png", renderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

int main(int argc, char** argv){

	if( !init() ){
		//Levantar el error.
	}
	else{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
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
					SDL_SetRenderDrawColor( renderer, 255, 255, 255, 1 );
					SDL_RenderClear( renderer );


					/*-----Ejemplo de uso de SPRITES------*/

					//creacion de sprites pasandole x, y, w, h
					Sprite bloque1(0, 0, 100, 100);
					Sprite bloque2(150, 150, 100, 100);
					Sprite bloque3(SCREEN_HEIGHT/2, SCREEN_WIDTH/2, 200, 200);

					//Le agrego la misma textura a dos de ellos
					bloque1.set_texture(&gBackgroundTexture);
					bloque2.set_texture(&gBackgroundTexture);

					//Al tercer bloque le defino solo un color de fondo
					bloque3.set_background_color(255,130,15);

					//Los agrego a un grupo de sprites y dibujo todas en el renderer
					SpriteGroup active_sprites;
					active_sprites.add(&bloque1);
					active_sprites.add(&bloque2);
					active_sprites.add(&bloque3);
					active_sprites.draw(renderer);




					//Update screen
					SDL_RenderPresent( renderer );

					control_framerate(starting_tick);
				}
			}
		}

	}
	close(window, renderer);
	return 0;
}
