#include "Pez.hpp"

#define WIDTH 150
#define HEIGHT 120
#define H 60

Pez::Pez(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("up");
    setRectangulo("up", 0, 0, 39, H);
    setRectangulo("up", 39, 0, 39, H);
    setRectangulo("up", 78, 0, 35, H);
    setRectangulo("up", 113, 0, 37, H);
    /*Sprites a derecha*/
    setClip("down");
    setRectangulo("down", 0, 60, 39, H);
    setRectangulo("down", 39, 60, 39, H);
    setRectangulo("down", 78, 60, 35, H);
    setRectangulo("down", 113, 60, 37, H);
    rectangle = clipsMovimientos->getRectangulo("up", 0);
}
