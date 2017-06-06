#include "StartButton.hpp"

#define W 520
#define H 150

StartButton::StartButton(int x, int y) : Button(x, y, W, H){
    /*Hay solo 2 botones asique solo se diferencia al clickear*/
    setRectangulo("mouseover", 0, 0, W, H);
    setRectangulo("mouseup", 0, 0, W, H);
    setRectangulo("mouseout", 0, 0, W, H);
    setRectangulo("mousedown", 260, 0, W, H);
    rectangle = clipsMovimientos->getRectangulo("mouseout", 0);
}

void StartButton::handleOnClick(){
    /*Aca debería conectarse al servidor y quedar en espera*/
}
