#include "MovingBloque.hpp"
using namespace std;

#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640

void MovingBloque::moveRight(float vel_x){}
void MovingBloque::moveLeft(float vel_x){}
void MovingBloque::jump(float,float){}

MovingBloque::MovingBloque(int x, int y, int w, int h,float vel_s):
  Bloque(x,y,w,h){
    velX=0.0;
    velY=0.0;
    velocidad=vel_s;
    frameRight = 0;
    frameLeft = 0;
    frameQuiet = 0;
    frameJumping = 0;
    clipsMovimientos = new ClipGroup();
    //La direccion se setea en true cuando esta para la derecha.
    direccion = true;
  }

/*Setters*/
void MovingBloque::setPosicionInicio(){}

void MovingBloque::setClip(string nombre){
  clipsMovimientos->addClip(nombre);
}

void MovingBloque::setRectangulo(string nombre, int x, int y, int w, int h){
  clipsMovimientos->addRectangulo(nombre,x,y,w,h);
}

void MovingBloque::printMap(){
  clipsMovimientos->printMap();
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
