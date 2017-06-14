#include "GameOverStage.hpp"

GameOverStage::GameOverStage(int w, int h) : Stage(){
    setDimensions(w, h);

    front = new Layer();
    front->setDimensions(w, h);
    front->setTexPath("Graficos/game_over.png");
    front->loadImage();
}

GameOverStage::~GameOverStage(){
    if (front){
        delete front;
        front = NULL;
    }
}

void GameOverStage::render(){
    front->render();
}
