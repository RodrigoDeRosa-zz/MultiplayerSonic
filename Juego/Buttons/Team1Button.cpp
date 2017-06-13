#include "Team1Button.hpp"
#include <stdio.h>

#define W 340
#define H 155

Team1Button::Team1Button(int x, int y) : StartButton(x, y, W, H){
}

key_event Team1Button::handleOnClick(){
    setUnusable();
    return START_TEAM_1;
    /*Avisa al servidor que se conecta en team1*/
}
