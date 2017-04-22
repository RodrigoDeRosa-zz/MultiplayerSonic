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

public:
  MovingBloque(int x, int y, int w, int h, int vel_s);
  void render(Camara* camara);
  virtual void moveRight(int frame, int cant_frames, float vel_x, int fact);
  virtual void moveLeft(int frame, int cant_frames, float vel_x, int fact);
  void setVelocidades();
};
#endif /*MOVINGBLOQUE_HPP*/
