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
/*SERVER*/
void Juego::updateJugadores(map <string, vector <int>> jug){
  /**Funcion que se utiliza desde el server para actualizar los jugadores.
  Recibe un mapa que contiene como clave el id de el jugador a actualizar,
  como valor un vector del ints [velX, velX, posX, posY, conectado].
  El int de conectado funciona como un booleano.
  Conectado == 1*/

  for (map<string,vector <int>>::iterator it=jug.begin(); it!=jug.end(); ++it){
    string id= it->first;
    vector <int> valores = it->second;
    updateJugador(id, valores[0], valores[1], valores[2], valores[3], valores [4]);
  }
}

void Juego::updateJugador(string id, int velx, int vely, int posx, int posy, int desconectado){

  //jugadores->updateJugador()
  // hay que seguir apartir de aca

}

/*VISTA*/
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
    //camara->render();
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
