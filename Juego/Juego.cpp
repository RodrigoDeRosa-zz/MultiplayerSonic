#include "Juego.hpp"
#include "../logger/current/Logger2.hpp"
#include "SegaFactory.hpp"

/*get sonic privada
 en jugadores que se cree un personaje generico*/
Juego::Juego(){
    jugadores = NULL;
    stageActual = NULL;
    camara = NULL;
}
/*SERVER*/
void Juego::updateJugadores(map <string, vector <float> > jug){
  /**Funcion que se utiliza desde el server para actualizar los jugadores.
  Recibe un mapa que contiene como clave el id de el jugador a actualizar,
  como valor un vector del ints [velX, velX, posX, posY, conectado].
  El int de conectado funciona como un booleano.
  Conectado == 1*/

  for (map<string,vector <float> >::iterator it=jug.begin(); it!=jug.end(); ++it){
    string id= it->first;
    vector <float> valores = it->second;
    updateJugador(id, valores[0], valores[1], valores[2], valores[3], valores [4]);
  }
}

void Juego::updateJugador(string id, float posx, float posy, move_type movimiento, int frame, bool conectado){

  jugadores->updateJugador(id, posx,posy, movimiento, frame, conectado);
}

void Juego::updateCamara(int posx, int posy){
  camara -> setPosicion(posx, posy);
}

bool Juego::addJugador(string nombreJugador, string nombrePersonaje){
  return jugadores->addJugador(nombreJugador,nombrePersonaje);
}

/*VISTA*/
void Juego::setStage(Stage* new_stage){
    stageActual = new_stage;
}

void Juego::setJugadores(Jugadores* jugs){
    jugadores=jugs;
}

// void Juego::actualizarJugadores(){
//     //tendria que recibir datos del servidor para actualizar la posicion de todos los jugadores
// }

void Juego::render(){
    //this.actualizarJugadores();
    stageActual->render(camara);
    //camara->render();
    jugadores->render(camara);
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
    if (stageActual){
        delete stageActual;
        stageActual = NULL;
    }
}
