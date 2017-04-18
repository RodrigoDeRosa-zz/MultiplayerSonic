#ifndef APUNTADO_HPP
#define APUNTADO_HPP

#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Apuntado : public Sprite{
public:
			Apuntado(int x, int y, int w, int h, int vel_s);
			void move(int AnchoEscenario, int AltoEscenario);
			void handleEvent( SDL_Event& e );

protected:
	int velocidad;
	int velX, velY;
};


#endif /*APUNTADO_HPP*/
