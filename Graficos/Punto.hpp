#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.hpp"

#ifndef PUNTO_H_
#define PUNTO_H_

class Punto{
    public:
		static const int ANCHO_PUNTO = 20;
		static const int ALTO_PUNTO = 20;
		static const int PUNTO_VEL = 10;

		Punto();

		void handleEvent( SDL_Event& e );

		void move();

		void render( int camX, int camY );

		int getPosX();
		int getPosY();

    private:
		Texture* texturaPunto;
		int posX, posY;
		int velX, velY;

		void inicializar();
};

#endif /* PUNTO_H_ */