#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>
using namespace std;

class Window{
    private:
        Window();//Constructor
        ~Window();//Destructor
        int width;
        int height;
        string title;
        SDL_Window* window;
    public:
        /*Metodo de obtencion de la instancia del Singleton*/
        static Window& getInstance();
        void setDimensions(int w, int h);
        void setTitle(string);
        int getWidth();
        int getHeight();
        /*Inicializacion de la ventana por medio de SDL*/
        bool init();
        /*Inicializacion del renderer por medio de SDL*/
        SDL_Renderer* initRenderer();
};

#endif /*WINDOW_HPP*/
