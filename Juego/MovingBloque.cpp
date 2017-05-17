#include "MovingBloque.hpp"
using namespace std;

#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640


MovingBloque::MovingBloque(float x, float y, int w, int h):
  Bloque(x,y,w,h){
    tiempoX=0.0;
    tiempoY=0.0;
    tiempoSalto=0.0;
    frameRight = 0;
    frameLeft = 0;
    frameQuiet = 0;
    frameJumping = 0;
    clipsMovimientos = new ClipGroup();
    //La direccion se setea en true cuando esta para la derecha.
    direccion = true;
    jumping = false;
  }

void MovingBloque::quietoDerecha(int){};
void MovingBloque::quietoIzquierda(int){};
void MovingBloque::caminarDerecha(int){};
void MovingBloque::caminarIzquierda(int){};
void MovingBloque::correrDerecha(int){};
void MovingBloque::correrIzquierda(int){};
void MovingBloque::jumpDerecha(int){};
void MovingBloque::jumpIzquierda(int){};

/*Setters*/

void MovingBloque::setClip(string nombre){
  clipsMovimientos->addClip(nombre);
}

void MovingBloque::setRectangulo(string nombre, float x, float y, int w, int h){
  clipsMovimientos->addRectangulo(nombre,x,y,w,h);
}

void MovingBloque::grisearTexture(){
  texture->setKeyColor(30, 30, 30);
  texture->setColorMod();
}

void MovingBloque::desGrisearTexture(){
  texture->setKeyColor(255, 255, 255);
  texture->setColorMod();
}

void MovingBloque::render(Camara* cam){
  //Si no tiene textura cargada, pinta con el color de fondo.
  float auxX = originX - cam->getX();
  float auxY = originY - cam->getY();
  Renderer::getInstance().setDrawColor(red, green, blue, 1);

  if(texture) texture->renderWithMovement(auxX, auxY, &rectangle);
      else{
        float aux1 = rectangle.x;
        float aux2 = rectangle.y;

          rectangle.x -= cam->getX();
          rectangle.y -= cam->getY();

          Renderer::getInstance().fillRect(&rectangle);

          rectangle.x = aux1;
          rectangle.y = aux2;
      }
}
