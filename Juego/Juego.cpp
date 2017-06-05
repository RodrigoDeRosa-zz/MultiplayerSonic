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
#include <sstream>
#include <string>
#include <fstream>
#include <string>
using namespace std;

#define SSTR( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()

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
    /*Textura de piedras*/
    Texture* piedras = new Texture();
    piedras->loadFromFile("Graficos/piedras.png");
    texturas.insert(make_pair("piedras", piedras));
    /*Textura de pinches*/
    Texture* pinches = new Texture();
    pinches->loadFromFile("Graficos/pinches.png");
    texturas.insert(make_pair("pinches", pinches));
    /*Textura de monedas*/
    Texture* monedas = new Texture();
    monedas->loadFromFile("Graficos/monedas.png");
    texturas.insert(make_pair("monedas", monedas));
    /*Textura de cangrejos*/
    Texture* cangrejos = new Texture();
    cangrejos->loadFromFile("Graficos/cangrejos.png");
    texturas.insert(make_pair("cangrejos", cangrejos));
    /*Textura de peces*/
    Texture* peces = new Texture();
    peces->loadFromFile("Graficos/pez.png");
    texturas.insert(make_pair("peces", peces));
    /*Textura de moscas*/
    Texture* moscas = new Texture();
    moscas->loadFromFile("Graficos/mosca.png");
    texturas.insert(make_pair("moscas", moscas));
    /*Textura de bonus*/
    Texture* bonus = new Texture();
    bonus->loadFromFile("Graficos/bonus.png");
    texturas.insert(make_pair("bonus", bonus));
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

void Juego::setStageScore(){
    stageActual->initScore();
}

void Juego::updateJugador(string id, float posx, float posy, move_type movimiento, int frame, bool conectado,
    int rings, int lives, int points){
    stageActual->updateScore(stoi(id), rings, lives, points, conectado);
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

void Juego::updateStageSprite(string groupKey, out_message_t* message){
    if (message->connection == false){
        stageActual->removeSprite(groupKey, message->id);
        return;
    }
    stageActual->updateSprite(groupKey, message->id, message->posX, message->posY);
}

void Juego::updateStageEntity(string groupKey, out_message_t* message){
    if (message->connection == false){
        stageActual->removeEntity(groupKey, message->id);
        return;
    }
    stageActual->updateEntity(groupKey, message->id, message->posX, message->posY, message->frame);
}

void Juego::updateStageEntitySense(string groupKey, out_message_t* message){
    if (message->connection == false){
        stageActual->removeEntity(groupKey, message->id);
        return;
    }
    stageActual->updateEntity(groupKey, message->id, message->posX, message->posY, message->frame, message->move);
}

void Juego::updateMoneda(out_message_t* message){
    updateStageEntity("monedas", message);
}

void Juego::updateCangrejo(out_message_t* message){
    updateStageEntity("cangrejos", message);
}

void Juego::updateMosca(out_message_t* message){
    updateStageEntitySense("moscas", message);
}

void Juego::updatePez(out_message_t* message){
    updateStageEntitySense("peces", message);
}

void Juego::updateBonus(out_message_t* message){
    updateStageEntity("bonus", message);
}

void Juego::addSpriteGroup(string groupKey){
    stageActual->addSpriteGroup(groupKey);
}

void Juego::addEntityGroup(string groupKey){
    stageActual->addEntityGroup(groupKey);
}

void Juego::addSprite(string groupKey, Sprite* sprite, int index){
    stageActual->addSprite(groupKey, sprite, index);
}

void Juego::addPiedra(float x, float y, int type, int index){
    Piedra* piedra = new Piedra(x, y, type);
    //Carga de textura
    map<string, Texture*>::iterator it;
    it = texturas.find("piedras");
    Texture* tex = it->second;
    piedra->setTexture(tex);
    piedra->setIndexZ(99);
    stageActual->addSprite("piedras", piedra, index);
}

/*Agrega pinches en las posiciones dadas*/
void Juego::addPinche(float x, float y, int index){
    Pinche* pinche = new Pinche(x, y);
    //Carga de textura
    map<string, Texture*>::iterator it;
    it = texturas.find("pinches");
    Texture* tex = it->second;
    pinche->setTexture(tex);
    pinche->setIndexZ(99);
    stageActual->addSprite("pinches", pinche, index);
}

/*Agrega una moneda en las posiciones dadas*/
void Juego::addMoneda(float x, float y, int index){
    Moneda* moneda = new Moneda(x, y);
    //Carga de textura
    map<string, Texture*>::iterator it;
    it = texturas.find("monedas");
    Texture* tex = it->second;
    moneda->setTexture(tex);
    moneda->setIndexZ(99);
    stageActual->addEntity("monedas", moneda, index);
}

/*Agrega un bonus en las posiciones dadas*/
void Juego::addBonus(float x, float y, int t, int index){
    Bonus* bonus = new Bonus(x, y, t);
    /*Aca habria que cargarle la textura de pinche*/
    map<string, Texture*>::iterator it;
    it = texturas.find("bonus");
    Texture* tex = it->second;
    bonus->setTexture(tex);
    bonus->setIndexZ(99);
    stageActual->addEntity("bonus", bonus, index);
}

/*Agrega un pez en las posiciones dadas*/
void Juego::addPez(float x, float y, int index){
    Pez* pez = new Pez(x, y);
    map<string, Texture*>::iterator it;
    it = texturas.find("peces");
    Texture* tex = it->second;
    pez->setTexture(tex);
    pez->setIndexZ(99);
    stageActual->addEntity("peces", pez, index);
}

/*Agrega un cangrejo en las posiciones dadas*/
void Juego::addCangrejo(float x, float y, int index){
    Cangrejo* cangrejo = new Cangrejo(x, y);
    //Carga de textura
    map<string, Texture*>::iterator it;
    it = texturas.find("cangrejos");
    Texture* tex = it->second;
    cangrejo->setTexture(tex);
    cangrejo->setIndexZ(99);
    stageActual->addEntity("cangrejos", cangrejo, index);
}

/*Agrega un pajaro en las posiciones dadas*/
void Juego::addMosca(float x, float y, int index){
    Mosca* mosca = new Mosca(x, y);
    map<string, Texture*>::iterator it;
    it = texturas.find("moscas");
    Texture* tex = it->second;
    mosca->setTexture(tex);
    mosca->setIndexZ(99);
    stageActual->addEntity("moscas", mosca, index);
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
