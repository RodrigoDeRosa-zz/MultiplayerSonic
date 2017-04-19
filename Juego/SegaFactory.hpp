#ifndef SEGAFACTORY_HPP
#define SEGAFACTORY_HPP

#include "Sonic.hpp"
#include <string>
#include <iostream>
using namespace std;

class SegaFactory{
  private:
    //tenemos qe hacer que get sonic sea privada
  public:
    Sonic* getSonic(string);
    SegaFactory();
    /*agregar todas las funciones de creacion de cada personaje
    recibe nombre valido del personaje y nombre del jugador
    si falla devuelve NULL*/
    bool getPersonaje(string, string, Personaje*);
};

#endif
