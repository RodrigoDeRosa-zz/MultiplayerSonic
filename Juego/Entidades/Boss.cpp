#include "Boss.hpp"

#define WIDTH 2880
#define HEIGHT 400
#define H 200
#define W 239

Boss::Boss(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("left");
    setRectangulo("left", 0, 0, W, H);
    setRectangulo("left", 239, 0, W, H);
    setRectangulo("left", 478, 0, W, H);
    setRectangulo("left", 717, 0, W, H);
    setRectangulo("left", 956, 0, W, H);
    setRectangulo("left", 1195, 0, W, H);
    setRectangulo("left", 1434, 0, W, H);
    setRectangulo("left", 1673, 0, W, H);
    setRectangulo("left", 1912, 0, W, H);
    setRectangulo("left", 2151, 0, W, H);
    setRectangulo("left", 2390, 0, W, H);
    setRectangulo("left", 2629, 0, W, H);
    /*Sprites a derecha*/
    setClip("right");
    setRectangulo("right", 0, 200, W, H);
    setRectangulo("right", 239, 200, W, H);
    setRectangulo("right", 478, 200, W, H);
    setRectangulo("right", 717, 200, W, H);
    setRectangulo("right", 956, 200, W, H);
    setRectangulo("right", 1195, 200, W, H);
    setRectangulo("right", 1434, 200, W, H);
    setRectangulo("right", 1673, 200, W, H);
    setRectangulo("right", 1912, 200, W, H);
    setRectangulo("right", 2151, 200, W, H);
    setRectangulo("right", 2390, 200, W, H);
    setRectangulo("right", 2629, 200, W, H);
    rectangle = clipsMovimientos->getRectangulo("right", 0);
}
