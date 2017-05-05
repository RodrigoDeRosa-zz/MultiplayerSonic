#include "ClipGroup.hpp"

ClipGroup::ClipGroup(){}

void ClipGroup::addClip(string nombre){
  Clip* aux = new Clip();
  clips[nombre]= aux;
}

void ClipGroup::addRectangulo(string nombre,int x, int y, int w, int h){
  Clip* aux = clips[nombre];
  aux->addRectangulo(x,y,w,h);
  //clips[nombre]->addRectangulo(x,y,w,h);
}

void ClipGroup::printMap(){

  for (map<string,Clip*>::iterator it=clips.begin(); it!=clips.end(); ++it){
    Clip* clip= it->second;
    clip->printClip();
  }
}

SDL_Rect ClipGroup::getRectangulo(string nombre, int frame){
  Clip* aux = clips[nombre];
  return aux->getRectangulo(frame);
}
