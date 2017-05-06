#ifndef MOVINGBLOQUE_HPP
#define MOVINGBLOQUE_HPP

#include "../Graficos/Bloque.hpp"
#include "../Graficos/Camara.hpp"
#include "../Graficos/Renderer.hpp"
#include "ClipGroup.hpp"
using namespace std;

class MovingBloque: public Bloque{
protected:
  int frameRight, frameLeft, frameQuiet,frameJumping;
  float velocidad,tiempoX,tiempoY, tiempoSalto;
  bool direccion, jumping;
  ClipGroup* clipsMovimientos;

public:
  MovingBloque(float x, float y, int w, int h);
  void render(Camara* camara);
  virtual void moveRight(float vel_x);
  virtual void moveLeft(float vel_x);
  virtual void jump(float,float);
  bool estaSaltando();

  void setClip(string);
  void setRectangulo(string, float, float, int, int);
  void printMap();

  void grisearTexture();
  void desGrisearTexture();

  virtual void setPosicionInicio();
};
#endif /*MOVINGBLOQUE_HPP*/
