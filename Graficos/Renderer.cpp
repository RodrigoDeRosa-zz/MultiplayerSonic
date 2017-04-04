#include "Window.hpp"
#include "Renderer.hpp"
#include <SDL2/SDL.h>
//#include <SDL2/SDL2_gfxPrimitives.h>
#include "Logger2.hpp"
#define PI 3.14159265
#define MAX_ARRAY 360

/*Constructor*/
Renderer::Renderer(){
    renderer = NULL;
}

/*Destructor*/
Renderer::~Renderer(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
}

/*Metodo de obtencion de una instancia del singleton*/
Renderer& Renderer::getInstance(){
    static Renderer instance;
    return instance;
}

/*Incializa el SDL_Renderer*/
bool Renderer::init(){
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
	    Logger::getInstance().log("In Renderer::init(): Linear texture filtering not enabled!",ALTO);
    }
    renderer = Window::getInstance().initRenderer();
    if(!renderer){
        Logger::getInstance().log("In Renderer::init(): Renderer could not be initialized!",MEDIO);
        return false;
    }
    setDrawColor(0x00, 0xFF, 0xFF, 0xFF);
}

/*Define el color de dibujado del renderer*/
void Renderer::setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    if(!renderer){
	    Logger::getInstance().log("In Renderer::SetDrawColor(): No renderer to set color to!");
        return;
    }
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

/*Crea una textura desde la superficie recibida*/
SDL_Texture* Renderer::getTextureFromSurface(SDL_Surface* surface){
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/*Renderiza la parte de la textura recibida dada por clip donde indica el renderQuad*/
void Renderer::renderTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* renderQuad){
    SDL_RenderCopy(renderer, tex, clip, renderQuad);
}
/*
//Parametriza un circulo generando sus coordenadas y carga la textura a el
void Renderer::renderCircleTexture(int x, int y, int r, SDL_Surface* texture){
	Sint16 v_x [MAX_ARRAY];
	Sint16 v_y [MAX_ARRAY];

	int i = 0; //angulo tita
	int pos = 0;
	for(i; i < MAX_ARRAY; i++){
		v_x[pos] = r * cos(i * PI / 180) + x;
		v_y[pos] = r * sin(i * PI / 180) + y;
		pos ++;
	}

	//printf("%i", pos);

	if(!texturedPolygon(renderer, v_x, v_y, pos, texture, x-r, y-r)){
		//printf("Circle texture unable to load \n");
		Logger::getInstance().log("In Renderer::renderCircleTexture(): Circle texture unable to load");
	}
}*/

/*Pinta el SDL_Rect recibido con el color de dibujado*/
void Renderer::fillRect(SDL_Rect* rect){
    SDL_RenderFillRect(renderer, rect);
}
/*
//Pinta el circulo de las caracteristicas recibidas con el color de dibujado
int Renderer::fillCircle(Sint16 x, Sint16 y, Sint16 radius, Uint8 red, Uint8 green, Uint8 blue){
	return filledCircleRGBA(renderer, x, y, radius, red, green, blue, 0xFF);
}*/

void Renderer::clear(){
    SDL_RenderClear(renderer);
}

void Renderer::draw(){
    SDL_RenderPresent(renderer);
}
