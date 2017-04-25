#ifndef CLIP_HPP
#define CLIP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
using namespace std;

class Clip{
  protected:
    vector <SDL_Rect> rectangulos;
    int tam;
  public:
    Clip();
    void addRectangulo(int, int, int, int);
    void printClip();
    SDL_Rect getRectangulo(int);
};
#endif /*CLIP_HPP*/
