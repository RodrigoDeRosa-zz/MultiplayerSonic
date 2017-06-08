#include "SonicLogo.hpp"

#define WIDTH 5200
#define HEIGHT 420
#define W 514
#define H 420

SonicLogo::SonicLogo(int x, int y) : Entity(x-W/2, y, WIDTH, HEIGHT){
    setClip("move");
    setRectangulo("move", 0, 0, W, H);
    setRectangulo("move", 514, 0, W, H);
    setRectangulo("move", 1028, 0, W, H);
    setRectangulo("move", 1542, 0, W, H);
    setRectangulo("move", 2056, 0, W, H);
    setRectangulo("move", 2570, 0, W, H);
    setRectangulo("move", 3084, 0, W, H);
    setRectangulo("move", 3598, 0, W, H);
    setRectangulo("move", 4112, 0, W, H);
    setRectangulo("move", 4626, 0, W, H);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}

void SonicLogo::render(){
    //Si no tiene textura cargada, pinta con el color de fondo.
    float auxX = originX;
    float auxY = originY;
    Renderer::getInstance().setDrawColor(red, green, blue, 1);

    texture->renderWithMovement(auxX, auxY, &rectangle);
}
