#include "Escudo.hpp"

#define WIDTH 1553
#define HEIGHT 363
#define W 171
#define H 181.5

Escudo::Escudo(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, W + 4, H);
    setRectangulo("move", 174, 0, W+1, H);
    setRectangulo("move", 346, 0, W, H);
    setRectangulo("move", 517, 0, W, H);
    setRectangulo("move", 688, 0, W, H);
    setRectangulo("move", 859, 0, W, H);
    setRectangulo("move", 1030, 0, W, H);
    setRectangulo("move", 1201, 0, W, H);
    setRectangulo("move", 1372, 0, W+1, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
