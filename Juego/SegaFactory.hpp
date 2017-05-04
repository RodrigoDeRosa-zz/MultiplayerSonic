#ifndef SEGAFACTORY_HPP
#define SEGAFACTORY_HPP

#include "Sonic.hpp"
#include "MovingSonic.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class SegaFactory{
  private:
    void initClips(MovingSonic*);
    //identificador de cuantos personajes se crearon para no repetir sus colores
    int idPers;
    //vector con la dirreccion de los distintos sprites
    vector<string> imagenes;
  public:
    Sonic* getSonic(string);
    SegaFactory();
};

#endif
