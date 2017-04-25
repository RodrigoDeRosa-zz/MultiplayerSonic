#ifndef MOVINGBLOQUE_HPP
#define MOVINGBLOQUE_HPP

#include "../Graficos/Bloque.hpp"
#include "../Graficos/Camara.hpp"
#include "../Graficos/Renderer.hpp"
#include "ClipGroup.hpp"
using namespace std;

class MovingBloque: public Bloque{
protected:
  int velocidad, frameRight, frameLeft, frameQuiet,frameJumping;
  float velX,velY;
  bool direccion;
  ClipGroup* clipsMovimientos;

public:
  MovingBloque(int x, int y, int w, int h, int vel_s);
  void render(Camara* camara);
  virtual void moveRight(float vel_x);
  virtual void moveLeft(float vel_x);
  virtual void jump(float,float);

  void setClip(string);
  void setRectangulo(string, int, int, int, int);
  void printMap();

  virtual void setPosicionInicio();
};
#endif /*MOVINGBLOQUE_HPP*/
