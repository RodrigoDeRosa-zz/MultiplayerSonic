#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <controlGrafico.cpp>
#include <controlGrafico.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char** argv){
	
	if( !init( window, renderer) ){
		//Levantar el error.
	}
}