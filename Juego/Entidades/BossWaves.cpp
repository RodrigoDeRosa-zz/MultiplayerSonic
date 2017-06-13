#include "BossWaves.hpp"

#define WIDTH 6000
#define HEIGHT 355
#define H 355
#define W 500

BossWaves::BossWaves(float x, float y) : Entity(x, y, WIDTH, HEIGHT){
    /*Sprites a izquierda*/
    setClip("move");
    for (int i = 0; i < 12; i++){
        setRectangulo("move", i*W, 0, W, H);
    }
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
