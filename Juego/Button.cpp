#include "Button.hpp"

Button::Button(int x, int y, int w, int h) : MovingBloque(x, y, w, h){
    box = {x, y, w/2, h/2};
    /*Se setean los clips basicos y despues cada subclase agrega su rectangulo
    con las dimensiones correspondientes en cada uno*/
    setClip("mouseover");
    setClip("mousedown");
    setClip("mouseou");
    setClip("mouseup");
}

bool Button::mouseOver(int x, int y){
    return ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
}

void Button::handleEvent(SDL_Event event){
    int x = event.motion.x;
    int y = event.motion.y;
    bool mouseOver = mouseOver(x, y);

    if(event.type == SDL_MOUSEMOTION){
        if(mouseOver) rectangle = clipsMovimientos->getRectangulo("mouseover", 0);
        else rectangle = clipsMovimientos->getRectangulo("mouseout", 0);
    } else if( event.type == SDL_MOUSEBUTTONDOWN ) {
        if(event.button.button == SDL_BUTTON_LEFT && mouseOver)
            rectangle = clipsMovimientos->getRectangulo("mousedown", 0);
    } else if( event.type == SDL_MOUSEBUTTONUP ){
        if(event.button.button == SDL_BUTTON_LEFT && mouseOver)
            rectangle = clipsMovimientos->getRectangulo("mouseup", 0);
    }
}
