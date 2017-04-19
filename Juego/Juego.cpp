#include "Juego.hpp"
#include "Logger2.hpp"
#include "SegaFactory.hpp"

/*get sonic privada
 en jugadores que se cree un personaje generico*/
Juego::Juego(){
    jugadores = NULL;
    stage = NULL;
    camara = NULL;
}

void Juego::setStage(Stage* new_stage){
    stage = new_stage;
}

void Juego::setJugadores(Jugadores* jugs){
    jugadores=jugs;
}

// void Juego::actualizarJugadores(){
//     //tendria que recibir datos del servidor para actualizar la posicion de todos los jugadores
// }

void Juego::render(){
    //this.actualizarJugadores();
    stage->render(camara);
    camara->render();
    jugadores->render(camara);
}

bool Juego::addJugador(string nombreJugador, string nombrePersonaje){
    return jugadores->addJugador(nombreJugador,nombrePersonaje);
}

void Juego::setFactory(){
    SegaFactory* fact = new SegaFactory();
    jugadores->setFactory(fact);
}

void Juego::setCamara(Camara* cam){
    camara = cam;
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
