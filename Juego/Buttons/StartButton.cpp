#include "StartButton.hpp"
#include <stdio.h>

#define W 436
#define H 208

StartButton::StartButton(int x, int y) : Button(x-W/4, y, W, H){
    /*Hay solo 2 botones asique solo se diferencia al clickear*/
    setRectangulo("mouseover", 0, 0, 218, 208);
    setRectangulo("mouseup", 0, 0, 218, 208);
    setRectangulo("mouseout", 0, 0, 218, 208);
    setRectangulo("mousedown", 218, 0, 218, 208);
    rectangle = clipsMovimientos->getRectangulo("mouseout", 0);
}

void StartButton::handleOnClick(){
    /*Aca debería conectarse al servidor y quedar en espera*/
}

void StartButton::render(){
    //Si no tiene textura cargada, pinta con el color de fondo.
    float auxX = originX;
    float auxY = originY;
    Renderer::getInstance().setDrawColor(red, green, blue, 1);

    texture->render(auxX, auxY, &rectangle);
}
