#ifndef MOVINGBLOQUE_HPP
#define MOVINGBLOQUE_HPP

#include "../Graficos/Bloque.hpp"
#include "../Graficos/Camara.hpp"
#include "../Graficos/Renderer.hpp"
using namespace std;

class MovingBloque: public Bloque{
protected:
  int velocidad;
  float velX,velY;
  int frameRight, frameLeft;

public:
  MovingBloque(int x, int y, int w, int h, int vel_s);
  void render(Camara* camara);
  virtual void moveRight(float vel_x);
  virtual void moveLeft(float vel_x);

  virtual void moveLef(int frameL, int cantF, float vel ,int fact);

  void setPosicionInicio();
};
#endif /*MOVINGBLOQUE_HPP*/
