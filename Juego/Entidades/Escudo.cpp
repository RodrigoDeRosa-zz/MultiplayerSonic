#include "Escudo.hpp"

#define WIDTH 1035
#define HEIGHT 242
#define W 114
#define H 121

Escudo::Escudo(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, W + 1, H);
    setRectangulo("move", 116, 0, W, H);
    setRectangulo("move", 231, 0, W, H);
    setRectangulo("move", 345, 0, W, H);
    setRectangulo("move", 459, 0, W, H);
    setRectangulo("move", 573, 0, W, H);
    setRectangulo("move", 687, 0, W, H);
    setRectangulo("move", 801, 0, W, H);
    setRectangulo("move", 915, 0, W+1, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
