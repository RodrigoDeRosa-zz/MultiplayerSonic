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
    //vector con la dirreccion de los distintos sprites
    vector<Texture*> texturas;
  public:
    Sonic* getSonic(string);
    SegaFactory();
};

#endif
