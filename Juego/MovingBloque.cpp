#include "MovingBloque.hpp"
using namespace std;

#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640

void MovingBloque::moveRight(int frame, int cant_frames, float vel_x, int fact){}
void MovingBloque::moveLeft(int frame, int cant_frames, float vel_x, int fact){}

MovingBloque::MovingBloque(int x, int y, int w, int h,int vel_s):
  Bloque(x,y,w,h){
    velX=0.0;
    velY=0.0;
    velocidad=vel_s;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 38.796992481;
    rectangle.h = 51;

  }

void MovingBloque::setVelocidades(){
    velX = 0.0;
    velY = 0.0;
}

void MovingBloque::render(Camara* cam){
  //Si no tiene textura cargada, pinta con el color de fondo.
  int auxX = originX - cam->getX();
  int auxY = originY - cam->getY();
  Renderer::getInstance().setDrawColor(red, green, blue, 1);

  if(texture) texture->renderWithMovement(auxX, auxY, &rectangle);
      else{
        int aux1 = rectangle.x;
        int aux2 = rectangle.y;

          rectangle.x -= cam->getX();
          rectangle.y -= cam->getY();

          Renderer::getInstance().fillRect(&rectangle);

          rectangle.x = aux1;
          rectangle.y = aux2;
      }
}
