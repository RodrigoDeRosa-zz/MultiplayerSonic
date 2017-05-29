#include "Moneda.hpp"

#define WIDTH 200
#define HEIGHT 40

Moneda::Moneda(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, 40, HEIGHT);
    setRectangulo("move", 40, 0, 40, HEIGHT);
    setRectangulo("move", 80, 0, 40, HEIGHT);
    setRectangulo("move", 120, 0, 40, HEIGHT);
    setRectangulo("move", 160, 0, 40, HEIGHT); //Este es cuando desaparece
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
