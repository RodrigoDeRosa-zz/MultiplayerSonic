#include "Cangrejo.hpp"

#define WIDTH 520
#define HEIGHT 55
#define W 86

Cangrejo::Cangrejo(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, W, HEIGHT);
    setRectangulo("move", 87, 0, W, HEIGHT);
    setRectangulo("move", 174, 0, W, HEIGHT);
    setRectangulo("move", 261, 0, W, HEIGHT);
    setRectangulo("move", 348, 0, W, HEIGHT);
    setRectangulo("move", 435, 0, W, HEIGHT);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
