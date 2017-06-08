#include "Team2Button.hpp"
#include <stdio.h>

#define W 340
#define H 155

Team2Button::Team2Button(int x, int y) : StartButton(x, y, W, H){
}

key_event Team2Button::handleOnClick(){
    return START_TEAM_2;
    /*Avisa al servidor que se conecta en team2*/
}
