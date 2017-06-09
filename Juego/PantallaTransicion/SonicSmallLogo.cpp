#include "SonicSmallLogo.hpp"

#define WIDTH 3696
#define HEIGHT 252
#define W 257
#define H 210

SonicSmallLogo::SonicSmallLogo(int x, int y) : Entity(x, y, WIDTH, HEIGHT){
    setClip("move");

    for (int i = 0; i < 14; i++){
        setRectangulo("move", i*W, 0, W, H);
    }
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}

void SonicSmallLogo::render(){
    Renderer::getInstance().setDrawColor(red, green, blue, 1);

    texture->renderWithMovement(originX, originY, &rectangle);
}
