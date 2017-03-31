#ifndef CIRCULO_HPP
#define CIRCULO_HPP

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Circulo: public Sprite {
	int radius;
	SDL_Surface* aux_texture;
public:
	Circulo(int x, int y, int r);
	void render(camara*);
	void setTexture(SDL_Surface* aux);
	//falta modificar el free
};

#endif
