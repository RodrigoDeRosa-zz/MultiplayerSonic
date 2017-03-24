#include <SDL2/SDL.h>
#include <string>
#include "Window.hpp"
using namespace std;

/*Constructor*/
Window::Window(){
    width = 0;
    height = 0;
    title = "";
    window = NULL;
}

/*Destructor*/
Window::~Window(){
    width = 0;
    height = 0;
    title = "";
    if(window){
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

/*Metodo de obtencion de instancia del singleton*/
Window& Window::getInstance(){
    static Window instance;
    return instance;
}

void Window::setDimensions(int w, int h){
    width = w;
    height = h;
}

int Window::getWidth(){
    return width;
}

int Window::getHeight(){
    return height;
}

void Window::setTitle(string s){
    title = s;
}

/*Inicializacion de la SDL_Window*/
bool Window::init(){
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    if(!window){
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

/*Inicializacion de SDL_Renderer*/
SDL_Renderer* Window::initRenderer(){
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
