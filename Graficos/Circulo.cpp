#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Circulo.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>




Circulo::Circulo(int x, int y, int r)
: Sprite(x, y, r, r){
	
	radius = r;
	//calculo el centro del circulo
	originX = x + (radius/2);
	originY = y + (radius/2);

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
            	//printf("Fail to fill circle color /n");
            }
        }
    }
