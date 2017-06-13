#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "MovingBloque.hpp"
#include "../message.hpp"
#include <SDL2/SDL.h>

class Button : public MovingBloque{
    protected:
        virtual key_event handleOnClick();
        SDL_Rect box;
        bool unusable;
        bool mouseOver(int x, int y);
        void setUnusable();
    public:
        Button(int x, int y, int w, int h);
        key_event handleEvent(SDL_Event);
};

#endif /*BUTTON_HPP*/
