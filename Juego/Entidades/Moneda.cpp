#include "Moneda.hpp"

#define WIDTH 200
#define HEIGHT 40

Moneda::Moneda(float x, float y) : MovingBloque(x, y, WIDTH, HEIGHT){
    frame = 0;

    setClip("rolling");
    setRectangulo("rolling", 0, 0, 40, HEIGHT);
    setRectangulo("rolling", 40, 0, 40, HEIGHT);
    setRectangulo("rolling", 80, 0, 40, HEIGHT);
    setRectangulo("rolling", 120, 0, 40, HEIGHT);
    setRectangulo("rolling", 160, 0, 40, HEIGHT); //Este es cuando desaparece
    rectangle = clipsMovimientos->getRectangulo("rolling", frame);
}

void Moneda::render(Camara* cam){
  //Si no tiene textura cargada, pinta con el color de fondo.
  float auxX = originX - cam->getX();
  float auxY = originY - cam->getY();
  Renderer::getInstance().setDrawColor(red, green, blue, 1);
  rectangle = clipsMovimientos->getRectangulo("rolling", frame);

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
