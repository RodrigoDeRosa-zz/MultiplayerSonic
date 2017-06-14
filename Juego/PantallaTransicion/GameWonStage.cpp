#include "GameWonStage.hpp"

GameWonStage::GameWonStage(int w, int h) : Stage(){
    setDimensions(w, h);

    front = new Layer();
    front->setDimensions(w, h);
    front->setTexPath("Graficos/partida_ganada.png");
    front->loadImage();
}

GameWonStage::~GameWonStage(){
    if (front){
        delete front;
        front = NULL;
    }
}

void GameWonStage::render(){
    front->render();
}
