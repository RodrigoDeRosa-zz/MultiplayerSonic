#include "BossWaves.hpp"

#define WIDTH 2880
#define HEIGHT 400
#define H 200
#define W 239

BossWaves::BossWaves(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("move");
    setRectangulo("move", 0, 0, W, H);
    setRectangulo("move", 239, 0, W, H);
    setRectangulo("move", 478, 0, W, H);
    setRectangulo("move", 717, 0, W, H);
    setRectangulo("move", 956, 0, W, H);
    setRectangulo("move", 1195, 0, W, H);
    setRectangulo("move", 1434, 0, W, H);
    setRectangulo("move", 1673, 0, W, H);
    setRectangulo("move", 1912, 0, W, H);
    setRectangulo("move", 2151, 0, W, H);
    setRectangulo("move", 2390, 0, W, H);
    setRectangulo("move", 2629, 0, W, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
