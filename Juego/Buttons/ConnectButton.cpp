#include "ConnectButton.hpp"
#include <stdio.h>

ConnectButton::ConnectButton(int x, int y, int w, int h) : Button(x, y, w, h){
    /*Hay solo 2 botones asique solo se diferencia al clickear*/
    setRectangulo("move", 0, 0, w/2, h);
    setRectangulo("move", w/2 + 5, 0, w/2, h);
    rectangle = clipsMovimientos->getRectangulo("move", 0);
}

key_event ConnectButton::handleOnClick(){
    return START_GAME; //!= KEY_TOTAL
    /*Aca debería conectarse al servidor y quedar en espera*/
}

void ConnectButton::render(){
    //Si no tiene textura cargada, pinta con el color de fondo.
    float auxX = originX;
    float auxY = originY;
    Renderer::getInstance().setDrawColor(red, green, blue, 1);

    texture->renderWithMovement(auxX, auxY, &rectangle);
}
