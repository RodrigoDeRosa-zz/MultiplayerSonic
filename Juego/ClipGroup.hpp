#ifndef CLIOGROUP_HPP
#define CLIOGROUP_HPP
#include "Clip.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <map>
using namespace std;

class ClipGroup{
  protected:
    map <string, Clip*> clips;
  public:
    ClipGroup();
    void addClip(string);
    void addRectangulo(string nombre,int x, int y, int w, int h);
    void printMap();
    SDL_Rect getRectangulo(string, int);

};

#endif /*CLIOGROUP_HPP*/
