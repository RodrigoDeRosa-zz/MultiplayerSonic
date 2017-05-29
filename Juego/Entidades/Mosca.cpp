#include "Mosca.hpp"

#define WIDTH 240
#define HEIGHT 120
#define H 30
#define W 30

Mosca::Mosca(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("left");
    setRectangulo("left", 0, 0, W, H);
    setRectangulo("left", 30, 0, W, H);
    setRectangulo("left", 60, 0, W, H);
    setRectangulo("left", 90, 0, W, H);
    setRectangulo("left", 120, 0, W, H);
    setRectangulo("left", 150, 0, W, H);
    setRectangulo("left", 180, 0, W, H);
    setRectangulo("left", 210, 0, W, H);
    setRectangulo("left", 0, 30, W, H);
    setRectangulo("left", 30, 30, W, H);
    setRectangulo("left", 60, 30, W, H);
    setRectangulo("left", 90, 30, W, H);
    setRectangulo("left", 120, 30, W, H);
    setRectangulo("left", 150, 30, W, H);
    setRectangulo("left", 180, 30, W, H);
    setRectangulo("left", 210, 30, W, H);
    /*Sprites a derecha*/
    setClip("right");
    setRectangulo("right", 0, 60, W, H);
    setRectangulo("right", 30, 60, W, H);
    setRectangulo("right", 60, 60, W, H);
    setRectangulo("right", 90, 60, W, H);
    setRectangulo("right", 120, 60, W, H);
    setRectangulo("right", 150, 60, W, H);
    setRectangulo("right", 180, 60, W, H);
    setRectangulo("right", 210, 60, W, H);
    setRectangulo("right", 0, 90, W, H);
    setRectangulo("right", 30, 90, W, H);
    setRectangulo("right", 60, 90, W, H);
    setRectangulo("right", 90, 90, W, H);
    setRectangulo("right", 120, 90, W, H);
    setRectangulo("right", 150, 90, W, H);
    setRectangulo("right", 180, 90, W, H);
    setRectangulo("right", 210, 90, W, H);
    rectangle = clipsMovimientos->getRectangulo("right", 0);
}
