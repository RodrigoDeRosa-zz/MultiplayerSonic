#include "Invencibilidad.hpp"

#define WIDTH 1035
#define HEIGHT 242
#define W 114
#define H 121

Invencibilidad::Invencibilidad(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, H, W + 1, H);
    setRectangulo("move", 116, H, W, H);
    setRectangulo("move", 231, H, W, H);
    setRectangulo("move", 345, H, W, H);
    setRectangulo("move", 459, H, W, H);
    setRectangulo("move", 573, H, W, H);
    setRectangulo("move", 687, H, W, H);
    setRectangulo("move", 801, H, W, H);
    setRectangulo("move", 915, H, W+1, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
