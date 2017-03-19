#include "Sprite.h"
#include "SDL2/SDL.h"
#include "LTexture.h"
#include <iostream>

LTexture* texture;
int origin_x, origin_y, width, height;

Sprite::Sprite(Uint8 r, Uint8 g, Uint8 b, int x, int y, int w, int h){

	//usar el color
	origin_x = x;
	origin_y = y;
	width = w;
	height = h;
	texture.set_background_color(r, g, b);

}

void Sprite::update() {
	//can be overridden!
}

void Sprite::set_texture(LTexture* new_texture){
	texture = new_texture;
	width = texture.getWidth();
	height = texture.getHeight();
}

void Sprite::draw(SDL_Renderer * destination){
	texture.render(origin_x, origin_y, destination);
}

void Sprite::set_background_color(Uint8 r, Uint8 g, Uint8 b){
	texture.set_background_color(r, g, b)
}

LTexture* Sprite::get_texture() const{
	return texture;
}

bool Sprite::operator==(const Sprite &other) const{
	return (texture == other.get_texture());
}
