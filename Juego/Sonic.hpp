#ifndef SONIC_HPP
#define SONIC_HPP

#include "Personaje.hpp"
#include <string>
#include <iostream>
using namespace std;

class Sonic: public Personaje {
  public:
    //recibe el nombre del jugador
    Sonic(string);
    void setEventMovimiento( SDL_Event& e );

};

#endif
