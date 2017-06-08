#include "Invencibilidad.hpp"

#define WIDTH 1553
#define HEIGHT 363
#define W 171
#define H 181.5

Invencibilidad::Invencibilidad(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, H, W + 4, H);
    setRectangulo("move", 174, H, W+1, H);
    setRectangulo("move", 346, H, W, H);
    setRectangulo("move", 517, H, W, H);
    setRectangulo("move", 688, H, W, H);
    setRectangulo("move", 859, H, W, H);
    setRectangulo("move", 1030, H, W, H);
    setRectangulo("move", 1201, H, W, H);
    setRectangulo("move", 1372, H, W+1, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
