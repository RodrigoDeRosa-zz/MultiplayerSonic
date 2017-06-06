#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "MovingBloque.hpp"
#include <SDL2/SDL.h>

class Button : public MovingBloque{
    private:
        SDL_Rect box;
        bool mouseOver(int x, int y);
    public:
        Button(int x, int y, int w, int h);
        void handleEvent(SDL_Event);
};

#endif /*BUTTON_HPP*/
