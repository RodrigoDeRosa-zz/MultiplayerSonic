#include "Juego.hpp"
#include "Logger2.hpp"

Juego::Juego(){
    jugadores = NULL;
    stage = NULL;
}

void Juego::setStage(Stage* new_stage){
    stage = new_stage;
}

// void Juego::actualizarJugadores(){
//     //tendria que recibir datos del servidor para actualizar la posicion de todos los jugadores
// }

void Juego::render(camara* camara){
    //this.actualizarJugadores();
    stage->render(camara);
}

Juego::~Juego(){
    if (jugadores){
        delete jugadores;
        jugadores = NULL;
    }
    if (stage){
        delete stage;
        stage = NULL;
    }
}
