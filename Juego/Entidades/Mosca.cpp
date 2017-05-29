#include "Mosca.hpp"

#define WIDTH 240
#define HEIGHT 120

Mosca::Mosca(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("left");
    setRectangulo("left", 0, 0, 40, HEIGHT);
    setRectangulo("left", 40, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 0, 0, 40, HEIGHT);
    setRectangulo("left", 40, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 0, 0, 40, HEIGHT);
    setRectangulo("left", 40, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 0, 0, 40, HEIGHT);
    setRectangulo("left", 40, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    setRectangulo("left", 80, 0, 40, HEIGHT);
    /*Sprites a derecha*/
    setClip("right");
    setRectangulo("right", 0, 0, 40, HEIGHT);
    setRectangulo("right", 40, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 0, 0, 40, HEIGHT);
    setRectangulo("right", 40, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 0, 0, 40, HEIGHT);
    setRectangulo("right", 40, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 0, 0, 40, HEIGHT);
    setRectangulo("right", 40, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    setRectangulo("right", 80, 0, 40, HEIGHT);
    rectangle = clipsMovimientos->getRectangulo("right", 0);
}
