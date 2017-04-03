#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Circulo.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Logger2.hpp"



Circulo::Circulo(int x, int y, int r)
: Sprite(x, y, r*2, r*2){
	
	radius = r;
	//calculo el centro del circulo
	originX = x + (radius);
	originY = y + (radius);

	//esta textura se podria cargar de afuera
	aux_texture = NULL;
}

void Circulo::setTexture(SDL_Surface* aux){
	aux_texture = aux;
//	aux->w = width;
//	aux->h = height;
}

void Circulo::render(camara* cam){
    //Si no tiene textura cargada, pinta con el color de fondo.
    int auxX = originX - cam->getX();
    int auyY = originY - cam->getY();

    if(aux_texture) Renderer::getInstance().renderCircleTexture(auxX, auyY, radius, aux_texture);
        else{
            if(!Renderer::getInstance().fillCircle((Sint16)auxX,(Sint16) auyY,(Sint16) radius, red, green, blue)){
            	Logger::getInstance().log("In Circulo::render: Failed to fill circle color");
            }
        }
    }
