#include "Mosca.hpp"

#define WIDTH 240
#define HEIGHT 120
#define H 60
#define W 56

Mosca::Mosca(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("left");
    setRectangulo("left", 0, 0, W, H);
    setRectangulo("left", 56, 0, W, H);
    setRectangulo("left", 112, 0, W, H);
    setRectangulo("left", 168, 0, W, H);
    /*Sprites a derecha*/
    setClip("right");
    setRectangulo("right", 0, 60, W, H);
    setRectangulo("right", 56, 60, W, H);
    setRectangulo("right", 112, 60, W, H);
    setRectangulo("right", 168, 60, W, H);
    rectangle = clipsMovimientos->getRectangulo("right", 0);
}
