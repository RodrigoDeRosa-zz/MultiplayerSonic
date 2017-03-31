#ifndef BLOQUE_HPP
#define BLOQUE_HPP


#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Bloque: public Sprite {
public:
	Bloque(int x, int y, int w, int h);
};

#endif