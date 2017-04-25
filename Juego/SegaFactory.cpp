#include "SegaFactory.hpp"
#define SONIC "Sonic"
using namespace std;

SegaFactory::SegaFactory(){
    /*mas adelante si esta la opcion de que alla mas de un Sonic
    se pueden cargar todas las texturas y sprites en la creacion
    de la factory*/
}

Sonic* SegaFactory::getSonic(string nomJugador){
      Sonic* sonic = new Sonic(nomJugador);
      //todos los sprites con sus texturas se tendrian que crear en el json loader
      /*creacion de el bloque */
      MovingSonic* bloque = new MovingSonic(100, 200, 1500, 3000, 1);
      Texture* tex = new Texture();
  		tex->loadFromFile("Graficos/sonicSprites.png");
  		bloque->setTexture(tex);

      sonic->setMovingBloque(bloque);

      initClips(bloque);

      //sonic->printMap();
      return sonic;
}

void SegaFactory::initClips(MovingSonic* sonic){

  sonic->setClip("caminarDer");
  sonic->setRectangulo("caminarDer",0,598,112,121);
  sonic->setRectangulo("caminarDer",112,598,112,121);
  sonic->setRectangulo("caminarDer",224,598,115,121);
  sonic->setRectangulo("caminarDer",339,598,100,121);
  sonic->setRectangulo("caminarDer",439,598,78,121);
  sonic->setRectangulo("caminarDer",517,598,78,121);
  sonic->setRectangulo("caminarDer",595,598,97,121);
  sonic->setRectangulo("caminarDer",692,598,117,121);
  sonic->setRectangulo("caminarDer",809,598,117,121);
  sonic->setRectangulo("caminarDer",926,598,100,121);
  sonic->setRectangulo("caminarDer",1026,598,79,121);
  sonic->setRectangulo("caminarDer",1105,598,79,121);
  sonic->setRectangulo("caminarDer",1184,598,85,121);
  sonic->setRectangulo("caminarDer",1269,598,90,121);

  sonic->setClip("caminarIzq");
  sonic->setRectangulo("caminarIzq",0,719,112,121);
  sonic->setRectangulo("caminarIzq",112,719,112,121);
  sonic->setRectangulo("caminarIzq",224,719,115,121);
  sonic->setRectangulo("caminarIzq",339,719,100,121);
  sonic->setRectangulo("caminarIzq",439,719,78,121);
  sonic->setRectangulo("caminarIzq",517,719,78,121);
  sonic->setRectangulo("caminarIzq",595,719,97,121);
  sonic->setRectangulo("caminarIzq",692,719,117,121);
  sonic->setRectangulo("caminarIzq",809,719,117,121);
  sonic->setRectangulo("caminarIzq",926,719,100,121);
  sonic->setRectangulo("caminarIzq",1026,719,79,121);
  sonic->setRectangulo("caminarIzq",1105,719,79,121);
  sonic->setRectangulo("caminarIzq",1184,719,85,121);
  sonic->setRectangulo("caminarIzq",1269,719,90,121);

  sonic->setClip("quietoDer");
  sonic->setRectangulo("quietoDer",0,1289,92,117);
  sonic->setRectangulo("quietoDer",92,1289,97,117);
  sonic->setRectangulo("quietoDer",189,1289,97,117);
  sonic->setRectangulo("quietoDer",286,1289,91,117);
  sonic->setRectangulo("quietoDer",377,1289,95,117);
  sonic->setRectangulo("quietoDer",472,1289,95,117);
  sonic->setRectangulo("quietoDer",567,1289,95,117);

  sonic->setClip("quietoIzq");
  sonic->setRectangulo("quietoIzq",0,1408,92,117);
  sonic->setRectangulo("quietoIzq",92,1408,97,117);
  sonic->setRectangulo("quietoIzq",189,1408,97,117);
  sonic->setRectangulo("quietoIzq",286,1408,91,117);
  sonic->setRectangulo("quietoIzq",377,1408,95,117);
  sonic->setRectangulo("quietoIzq",472,1408,95,117);
  sonic->setRectangulo("quietoIzq",567,1408,95,117);

  sonic->setClip("correrDer");
  sonic->setRectangulo("correrDer",0,840,96,109);
  sonic->setRectangulo("correrDer",96,840,96,109);
  sonic->setRectangulo("correrDer",192,840,96,109);
  sonic->setRectangulo("correrDer",288,840,96,109);
  sonic->setRectangulo("correrDer",384,840,96,109);
  sonic->setRectangulo("correrDer",480,840,88,109);
  sonic->setRectangulo("correrDer",568,840,98,109);
  sonic->setRectangulo("correrDer",666,840,95,109);

  sonic->setClip("correrIzq");
  sonic->setRectangulo("correrIzq",0,949,96,109);
  sonic->setRectangulo("correrIzq",96,949,96,109);
  sonic->setRectangulo("correrIzq",192,949,96,109);
  sonic->setRectangulo("correrIzq",288,949,96,109);
  sonic->setRectangulo("correrIzq",384,949,96,109);
  sonic->setRectangulo("correrIzq",480,949,88,109);
  sonic->setRectangulo("correrIzq",568,949,98,109);
  sonic->setRectangulo("correrIzq",666,949,95,109);
}
