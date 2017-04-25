#ifndef SEGAFACTORY_HPP
#define SEGAFACTORY_HPP

#include "Sonic.hpp"
#include "MovingSonic.hpp"
#include <string>
#include <iostream>
using namespace std;

class SegaFactory{
  private:
    void initClips(MovingSonic*);

  public:
    Sonic* getSonic(string);
    SegaFactory();
};

#endif
