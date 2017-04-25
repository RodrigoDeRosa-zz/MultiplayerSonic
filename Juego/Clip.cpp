#include "Clip.hpp"

Clip::Clip(){
  tam = 0;
}

void Clip::addRectangulo(int x, int y, int w, int h){
  SDL_Rect aux = {x, y, w, h};
  rectangulos.push_back(aux);
  tam++;
}

void Clip::printClip(){
  for(int x=0; x<tam; x++){
    printf("%d, %d, %d, %d", rectangulos[x].x,rectangulos[x].y, rectangulos[x].w,rectangulos[x].h);
  }
}

SDL_Rect Clip::getRectangulo(int frame){
    return rectangulos[frame];
}
