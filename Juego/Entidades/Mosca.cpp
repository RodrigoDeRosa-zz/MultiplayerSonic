#include "Mosca.hpp"

#define WIDTH 240
#define HEIGHT 120
#define H 30
#define W 25

Mosca::Mosca(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("left");
    setRectangulo("left", 0, 0, W, H);
    setRectangulo("left", 27, 0, W, H);
    setRectangulo("left", 56, 0, W, H);
    setRectangulo("left", 84, 0, W, H);
    setRectangulo("left", 112, 0, W, H);
    setRectangulo("left", 140, 0, W, H);
    setRectangulo("left", 168, 0, W, H);
    setRectangulo("left", 196, 0, W, H);
    setRectangulo("left", 0, 30, W, H);
    setRectangulo("left", 27, 30, W, H);
    setRectangulo("left", 56, 30, W, H);
    setRectangulo("left", 84, 30, W, H);
    setRectangulo("left", 112, 30, W, H);
    setRectangulo("left", 140, 30, W, H);
    setRectangulo("left", 168, 30, W, H);
    setRectangulo("left", 196, 30, W, H);
    /*Sprites a derecha*/
    setClip("right");
    setRectangulo("right", 0, 60, W, H);
    setRectangulo("right", 27, 60, W, H);
    setRectangulo("right", 56, 60, W, H);
    setRectangulo("right", 84, 60, W, H);
    setRectangulo("right", 112, 60, W, H);
    setRectangulo("right", 140, 60, W, H);
    setRectangulo("right", 168, 60, W, H);
    setRectangulo("right", 196, 60, W, H);
    setRectangulo("right", 0, 90, W, H);
    setRectangulo("right", 27, 90, W, H);
    setRectangulo("right", 56, 90, W, H);
    setRectangulo("right", 84, 90, W, H);
    setRectangulo("right", 112, 90, W, H);
    setRectangulo("right", 140, 90, W, H);
    setRectangulo("right", 168, 90, W, H);
    setRectangulo("right", 196, 90, W, H);
    rectangle = clipsMovimientos->getRectangulo("right", 0);
}
