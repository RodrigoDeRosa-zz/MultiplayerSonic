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
  sonic->setRectangulo("caminarDer",0,726,112,121);
  sonic->setRectangulo("caminarDer",112,726,112,121);
  sonic->setRectangulo("caminarDer",224,726,115,121);
  sonic->setRectangulo("caminarDer",339,726,100,121);
  sonic->setRectangulo("caminarDer",439,726,78,121);
  sonic->setRectangulo("caminarDer",517,726,78,121);
  sonic->setRectangulo("caminarDer",595,726,97,121);
  sonic->setRectangulo("caminarDer",692,726,117,121);
  sonic->setRectangulo("caminarDer",809,726,117,121);
  sonic->setRectangulo("caminarDer",926,726,100,121);
  sonic->setRectangulo("caminarDer",1026,726,79,121);
  sonic->setRectangulo("caminarDer",1105,726,79,121);
  sonic->setRectangulo("caminarDer",1184,726,85,121);
  sonic->setRectangulo("caminarDer",1269,726,90,121);

  sonic->setClip("caminarIzq");
  sonic->setRectangulo("caminarIzq",0,847,112,121);
  sonic->setRectangulo("caminarIzq",112,847,112,121);
  sonic->setRectangulo("caminarIzq",224,847,115,121);
  sonic->setRectangulo("caminarIzq",339,847,100,121);
  sonic->setRectangulo("caminarIzq",439,847,78,121);
  sonic->setRectangulo("caminarIzq",517,847,78,121);
  sonic->setRectangulo("caminarIzq",595,847,97,121);
  sonic->setRectangulo("caminarIzq",692,847,117,121);
  sonic->setRectangulo("caminarIzq",809,847,117,121);
  sonic->setRectangulo("caminarIzq",926,847,100,121);
  sonic->setRectangulo("caminarIzq",1026,847,79,121);
  sonic->setRectangulo("caminarIzq",1105,847,79,121);
  sonic->setRectangulo("caminarIzq",1184,847,85,121);
  sonic->setRectangulo("caminarIzq",1269,847,90,121);

  sonic->setClip("quietoDer");
  sonic->setRectangulo("quietoDer",0,1452,92,121);
  sonic->setRectangulo("quietoDer",92,1452,97,121);
  sonic->setRectangulo("quietoDer",189,1452,97,121);
  sonic->setRectangulo("quietoDer",286,1452,91,121);
  sonic->setRectangulo("quietoDer",377,1452,95,121);
  sonic->setRectangulo("quietoDer",472,1452,95,121);
  sonic->setRectangulo("quietoDer",567,1452,95,121);

  sonic->setClip("quietoIzq");
  sonic->setRectangulo("quietoIzq",0,1573,92,121);
  sonic->setRectangulo("quietoIzq",92,1573,97,121);
  sonic->setRectangulo("quietoIzq",189,1573,97,121);
  sonic->setRectangulo("quietoIzq",286,1573,91,121);
  sonic->setRectangulo("quietoIzq",377,1573,95,121);
  sonic->setRectangulo("quietoIzq",472,1573,95,121);
  sonic->setRectangulo("quietoIzq",567,1573,95,121);

  sonic->setClip("correrDer");
  sonic->setRectangulo("correrDer",0,968,96,121);
  sonic->setRectangulo("correrDer",96,968,96,121);
  sonic->setRectangulo("correrDer",192,968,96,121);
  sonic->setRectangulo("correrDer",288,968,96,121);
  sonic->setRectangulo("correrDer",384,968,96,121);
  sonic->setRectangulo("correrDer",480,968,88,121);
  sonic->setRectangulo("correrDer",568,968,98,121);
  sonic->setRectangulo("correrDer",666,968,95,121);

  sonic->setClip("correrIzq");
  sonic->setRectangulo("correrIzq",0,1089,96,121);
  sonic->setRectangulo("correrIzq",96,1089,96,121);
  sonic->setRectangulo("correrIzq",192,1089,96,121);
  sonic->setRectangulo("correrIzq",288,1089,96,121);
  sonic->setRectangulo("correrIzq",384,1089,96,121);
  sonic->setRectangulo("correrIzq",480,1089,88,121);
  sonic->setRectangulo("correrIzq",568,1089,98,121);
  sonic->setRectangulo("correrIzq",666,1089,95,121);
}
