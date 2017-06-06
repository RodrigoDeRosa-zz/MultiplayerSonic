#include "SonicLogo.hpp"

#define WIDTH 5200
#define HEIGHT 420
#define W 514
#define H 420

SonicLogo::SonicLogo(int x, int y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");
    for (int i = 0; i < 10; i++){
        setRectangulo("move", i*W, 0, W, H);
    }
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}
