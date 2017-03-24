#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>

class Renderer{
    private:
        Renderer();//Constructor
        ~Renderer();//Destructor
        SDL_Renderer* renderer;
    public:
        /*Metodo de obtencion de la instancia del singleton*/
        static Renderer& getInstance();
        /*Inicializa el SDL_Renderer*/
        bool init();
        /*Crea una textura desde la superficie recibida*/
        SDL_Texture* getTextureFromSurface(SDL_Surface*);
        /*Renderiza la textura recibida bajo la firma de RenderCopy(r, tex, clip, quad)*/
        void renderTexture(SDL_Texture*, SDL_Rect*, SDL_Rect*);
        /*Define el color de dibujado del renderer*/
        void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        /*Pinta el SDL_Rect recibido con el color de dibujado*/
        void fillRect(SDL_Rect*);
        /*Hace RenderPresent sobre la pantalla*/
        void draw();
        /*Limpia el SDL_Renderer*/
        void clear();
};

#endif /*RENDERER_HPP*/
