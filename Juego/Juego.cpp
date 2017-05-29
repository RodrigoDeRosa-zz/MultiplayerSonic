#include "Juego.hpp"
#include "../logger/current/Logger2.hpp"
#include "SegaFactory.hpp"
#include "Entidades/Piedra.hpp"
#include "Entidades/Pinche.hpp"
#include "Entidades/Moneda.hpp"
#include "Entidades/Bonus.hpp"
#include "Entidades/Cangrejo.hpp"
#include "Entidades/Mosca.hpp"
#include "Entidades/Pez.hpp"

#define PIEDRA1W 124
#define PIEDRA1H 200
#define PIEDRA2W 103
#define PIEDRA2H 100
#define PIEDRA3W 113
#define PIEDRA3H 63

/*get sonic privada
 en jugadores que se cree un personaje generico*/
Juego::Juego(){
    jugadores = NULL;
    stageActual = NULL;
    camara = NULL;
    setTexturas();
}

void Juego::setTexturas(){
    //TODO: Llenar el mapa texturas con lo que corresponda:
    Texture* piedras = new Texture();
    piedras->loadFromFile("Graficos/piedras.png");
    texturas.insert(make_pair("piedras", piedras));
    /*
    Moneda, Cangrejo, Pez, pinche..
    */
}
/*SERVER*/
//void Juego::updateJugadores(map <string, vector <float> > jug){
//  /**Funcion que se utiliza desde el server para actualizar los jugadores.
//  Recibe un mapa que contiene como clave el id de el jugador a actualizar,
//  como valor un vector del ints [velX, velX, posX, posY, conectado].
//  El int de conectado funciona como un booleano.
//  Conectado == 1*/
//
////  for (map<string,vector <float> >::iterator it=jug.begin(); it!=jug.end(); ++it){
////    string id= it->first;
////    vector <float> valores = it->second;
////    updateJugador(id, valores[0], valores[1], valores[2], valores[3], valores [4]);
////  }
//}

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

void Juego::addStage(Stage* stage){
    if (stages.empty()){
        stageActual = stage;
        stageActualIndex = 0;
    }
    stages.push_back(stage);
}

void Juego::nextStage(){
    if (stageActualIndex == stages.size()){
        printf("No hay mas escenarios!\n");
        return;
    }
    stageActualIndex++;
    stageActual = stages[stageActualIndex];
}

void Juego::updateStage(string groupKey, int index, float x, float y){
    stageActual->updateSprite(groupKey, index, x, y);
}

void Juego::addSpriteGroup(string groupKey){
    stageActual->addSpriteGroup(groupKey);
}

void Juego::addSprite(string groupKey, Sprite* sprite){
    stageActual->addSprite(groupKey, sprite);
}

void Juego::addPiedra(float x, float y, int type){
    Piedra* piedra = new Piedra(x, y, type);
    //Carga de textura
    map<string, Texture*>::iterator it;
    it = texturas.find("piedras");
    Texture* tex = it->second;
    piedra->setTexture(tex);
    piedra->setIndexZ(99);
    stageActual->addSprite("piedras", piedra);
}

/*Agrega pinches en las posiciones dadas*/
void Juego::addPinche(float x, float y){
    Pinche* pinche = new Pinche(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    pinche->setBackgroundColor(0, 0, 0);
    pinche->setIndexZ(99);
    stageActual->addSprite("pinches", pinche);
}

/*Agrega una moneda en las posiciones dadas*/
void Juego::addMoneda(float x, float y){
    Moneda* moneda = new Moneda(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    moneda->setBackgroundColor(200, 200, 0);
    moneda->setIndexZ(99);
    stageActual->addSprite("monedas", moneda);
}

/*Agrega un bonus en las posiciones dadas*/
void Juego::addBonus(float x, float y){
    Bonus* bonus = new Bonus(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    bonus->setBackgroundColor(80, 80, 80);
    bonus->setIndexZ(99);
    stageActual->addSprite("bonus", bonus);
}

/*Agrega un pez en las posiciones dadas*/
void Juego::addPez(float x, float y){
    Pez* pez = new Pez(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    pez->setBackgroundColor(255, 0, 0);
    pez->setIndexZ(99);
    stageActual->addSprite("peces", pez);
}

/*Agrega un cangrejo en las posiciones dadas*/
void Juego::addCangrejo(float x, float y){
    Cangrejo* cangrejo = new Cangrejo(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    cangrejo->setBackgroundColor(0, 250, 0);
    cangrejo->setIndexZ(99);
    stageActual->addSprite("cangrejos", cangrejo);
}

/*Agrega un pajaro en las posiciones dadas*/
void Juego::addMosca(float x, float y){
    Mosca* mosca = new Mosca(x, y);
    /*Aca habria que cargarle la textura de pinche*/
    mosca->setBackgroundColor(0, 0, 250);
    mosca->setIndexZ(99);
    stageActual->addSprite("moscas", mosca);
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
