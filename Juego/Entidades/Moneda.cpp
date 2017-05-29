#include "Moneda.hpp"

#define WIDTH 200
#define HEIGHT 40

Moneda::Moneda(float x, float y) : MovingBloque(x, y, WIDTH, HEIGHT){
    frame = 0;

    setClip("rolling");
    setRectangulo("rolling", 0, 0, 40, HEIGHT);
    setRectangulo("rolling", 40, 0, 40, HEIGHT);
    setRectangulo("rolling", 80, 0, 40, HEIGHT);
    setRectangulo("rolling", 120, 0, 40, HEIGHT);
    setRectangulo("rolling", 160, 0, 40, HEIGHT); //Este es cuando desaparece
    rectangle = clipsMovimientos->getRectangulo("rolling", frame);
}

void Moneda::incFrame(){
    frame++;
    if (frame > 3) frame = 0;
    rectangle = clipsMovimientos->getRectangulo("rolling", frame);
}
