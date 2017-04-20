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
      Bloque* bloque = new Bloque(100, 200, 50, 50);
      sonic->setBloque(bloque);
      return sonic;
}
