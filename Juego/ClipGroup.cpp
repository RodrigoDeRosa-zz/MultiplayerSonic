#include "ClipGroup.hpp"
#include "../logger/current/Logger2.hpp"

ClipGroup::ClipGroup(){}

void ClipGroup::addClip(string nombre){
  Clip* aux = new Clip();
  if(aux==NULL){
    string mensaje = "El clip de accion: ";
    mensaje += nombre;
    mensaje += "no se pudo inicializar \n";
    Logger::getInstance().log(mensaje,MEDIO);
  }
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
