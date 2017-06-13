#include "ConnectionLostStage.hpp"

ConnectionLostStage::ConnectionLostStage(int w, int h) : Stage(){
    setDimensions(w, h);

    front = new Layer();
    front->setDimensions(w, h);
    front->setTexPath("Graficos/game_over.png");
    front->loadImage();
}

ConnectionLostStage::~ConnectionLostStage(){
    if (front){
        delete front;
        front = NULL;
    }
}

void ConnectionLostStage::render(){
    front->render();
}
