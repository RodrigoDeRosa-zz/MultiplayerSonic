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

  virtual void quietoDerecha(int);
  virtual void quietoIzquierda(int);
  virtual void caminarDerecha(int);
  virtual void caminarIzquierda(int);
  virtual void correrDerecha(int);
  virtual void correrIzquierda(int);
  virtual void jumpDerecha(int);
  virtual void jumpIzquierda(int);
  virtual void damageDerecha(int);
  virtual void damageIzquierda(int);
  virtual void esperandoDerecha(int);
  virtual void esperandoIzquierda(int);

  MovingBloque(float x, float y, int w, int h);
  void render(Camara* camara);

  void setClip(string);
  void setRectangulo(string, float, float, int, int);

  void grisearTexture();
  void desGrisearTexture();

};
#endif /*MOVINGBLOQUE_HPP*/
