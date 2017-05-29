#include "Cangrejo.hpp"

#define WIDTH 520
#define HEIGHT 55

Cangrejo::Cangrejo(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, 86, HEIGHT);
    setRectangulo("move", 87, 0, 86, HEIGHT);
    setRectangulo("move", 174, 0, 86, HEIGHT);
    setRectangulo("move", 261, 0, 86, HEIGHT);
    setRectangulo("move", 348, 0, 86, HEIGHT);
    setRectangulo("move", 435, 0, 86, HEIGHT);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
