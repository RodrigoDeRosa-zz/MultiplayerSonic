#include "SegaFactory.hpp"
#include "MovingSonic.hpp"
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
      MovingSonic* bloque = new MovingSonic(100, 200, 1032, 1943, 1);

      Texture* tex = new Texture();
  		tex->loadFromFile("Graficos/sonic_sprites.png");
  		bloque->setTexture(tex);

      sonic->setMovingBloque(bloque);
      return sonic;
}
