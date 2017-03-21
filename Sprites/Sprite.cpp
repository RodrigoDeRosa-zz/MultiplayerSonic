#include "Sprite.hpp"
#include "SDL2/SDL.h"
#include "LTexture.hpp"
#include <iostream>

LTexture* texture;
SDL_Rect rectangle;
int origin_x, origin_y, width, height, r, g, b;

Sprite::Sprite(int x, int y, int w, int h){

	texture = NULL;

	origin_x = x;
	origin_y = y;
	width = w;
	height = h;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.h = h;
	rectangle.w = w;

	//inicializo los el color blanco por defecto
	r = 255;
	g = 255;
	b = 255;
}

void Sprite::update() {
	//can be overridden!
}

void Sprite::set_texture(LTexture* new_texture){
	texture = new_texture;
}

void Sprite::draw(SDL_Renderer * destination){
	//si no tiene una textura cargada, entonces pinta el color ya definido
	if (texture != NULL){
		texture->render(origin_x, origin_y, &rectangle, destination);
	}
	else{
		SDL_SetRenderDrawColor( destination, r, g, b, 1 );
		SDL_RenderFillRect(destination, &rectangle);
	}
}

void Sprite::set_background_color(int new_r, int new_g, int new_b){
	r = new_r;
	g = new_g;
	b = new_b;
}

LTexture* Sprite::get_texture(){
	return texture;
}

bool Sprite::operator==(Sprite &other) const{
	return (texture == other.get_texture());
}
