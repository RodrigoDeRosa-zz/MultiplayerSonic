#include "Button.hpp"

Button::Button(int x, int y, int w, int h) : MovingBloque(x, y, w, h){
    box = {x, y, w, h};
    /*Se setean los clips basicos y despues cada subclase agrega su rectangulo
    con las dimensiones correspondientes en cada uno*/
    setClip("move");
}

bool Button::mouseOver(int x, int y){
    return ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h));
}

key_event Button::handleOnClick(){
    //Virtual
}

key_event Button::handleEvent(SDL_Event event){
    int x = event.motion.x;
    int y = event.motion.y;
    bool bMouseOver = mouseOver(x, y);

    if( event.type == SDL_MOUSEBUTTONDOWN ) {
        if(event.button.button == SDL_BUTTON_LEFT && bMouseOver){
            rectangle = clipsMovimientos->getRectangulo("move", 1);
            return handleOnClick();
        }
    } else if( event.type == SDL_MOUSEBUTTONUP ){
        if(event.button.button == SDL_BUTTON_LEFT && bMouseOver)
            rectangle = clipsMovimientos->getRectangulo("move", 0);
    }
    return KEY_TOTAL;
}
