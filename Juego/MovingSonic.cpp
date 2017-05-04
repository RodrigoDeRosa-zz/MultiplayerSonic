#include "MovingSonic.hpp"
#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640
#define CONTROL_MOVIMIENTO 0.001
#define CONTROL_CAMINATA 1.0
#define CONTROL_SALTO 1.0
#define GRAVEDAD 0.3
#define SALTO -12.0
#define WALKING_ANIMATION_FRAMES 14
#define RUNNING_ANIMATION_FRAMES 8
#define JUMPING_ANIMATION_FRAMES 5
#define QUIET_ANIMATION_FRAMES 7

#define QUIETOD "quietoDer"
#define QUIETOI "quietoIzq"
#define CAMINARD "caminarDer"
#define CAMINARI "caminarIzq"
#define CORRERD "correrDer"
#define CORRERI "correrIzq"
#define SALTARD "saltarDer"
#define SALTARI "saltarIzq"
#define FACTOR 12

MovingSonic::MovingSonic(int x, int y, int w, int h, float vel_s):
  MovingBloque(x,y,w,h, vel_s){
  }

void MovingSonic::setPosicionInicio(){
  tiempoX = 0.0;
  tiempoY = 0.0;
  tiempoSalto = 0.0;
  frameLeft=0;
  frameRight=0;
  frameJumping=0;

  if( frameQuiet / (FACTOR*QUIET_ANIMATION_FRAMES) >= QUIET_ANIMATION_FRAMES){
    frameQuiet=0;
  }
  //si esta apuntando para la derecha
  if(direccion){
    rectangle = clipsMovimientos->getRectangulo(QUIETOD,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
  }
  else{
    rectangle = clipsMovimientos->getRectangulo(QUIETOI,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
  }
  frameQuiet++;
}

void MovingSonic::jump(float vel_x,float vel_y){

  if( frameJumping / (6*JUMPING_ANIMATION_FRAMES) >= JUMPING_ANIMATION_FRAMES){
     frameJumping=0;
  }
  if(tiempoY == 0 && not jumping){
    tiempoY = SALTO;
    jumping = true;
    printf("SETEO LA VELOCIDAD\n" );
  }

  //velH cambiarlo por vel_X
  float velH = 0;
  if(vel_x>0){
    velH = 4.0;
  }
  if(vel_x<0){
    velH = -3.0;
  }

  originX += velH * tiempoSalto;
  originY += (tiempoY * tiempoSalto);
  tiempoY += (GRAVEDAD * tiempoSalto);
  rectangle = clipsMovimientos->getRectangulo(SALTARD,(frameJumping)/(6*JUMPING_ANIMATION_FRAMES));
  printf("velocidad en y %f posicion en y %f \n", tiempoY, originY);
  tiempoSalto += CONTROL_MOVIMIENTO;
  frameJumping ++;

  //Este chequeo se hace para que vuelva a empezar de 0 el salto.
  if(tiempoY >= (SALTO*-1) && jumping){
    tiempoSalto = 0.0;
    jumping = false;
    tiempoY = 0.0;
    printf("SETEO EL FRENADO\n");
  }

}


void MovingSonic::moveRight(float vel_x){

    //Si la velocidad era menor a 0, se movia para la izquierda.
    if(tiempoX <= 0.0){
      direccion = true;
      frameLeft = 0;
      frameQuiet=0;
      tiempoX = 0.0;
    }
    //Actualizamos el control de movimiento
    tiempoX += CONTROL_MOVIMIENTO;

    if (tiempoX<CONTROL_CAMINATA){caminarDerecha();}
    else if(tiempoX>=CONTROL_CAMINATA){correrDerecha();}

    //Actualizamos el frame
    frameRight++;

    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void MovingSonic::moveLeft(float vel_x){
  //Si la velocidad era mayor a 0, se movia para la derecha
  if(tiempoX >= 0.0){
    direccion = false;
    frameRight =0;
    frameQuiet=0;
    tiempoX = 0.0;
  }
  //Actualizamos el control de movimiento.
  tiempoX -= CONTROL_MOVIMIENTO;

  if(tiempoX > -CONTROL_CAMINATA){caminarIzquierda();}
  else if(tiempoX <= -CONTROL_CAMINATA){correrIzquierda();}

  //actualizamos el frame
  frameLeft++;

  if( originX < 0 ){originX = 0;}
}

void MovingSonic::caminarDerecha(){
  if( frameRight / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
    frameRight=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CAMINARD,frameRight/WALKING_ANIMATION_FRAMES);
  originX += velocidad;
}

void MovingSonic::caminarIzquierda(){
  if( frameLeft / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
    frameLeft=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CAMINARI,frameLeft/WALKING_ANIMATION_FRAMES);
  originX -= velocidad;
}

void MovingSonic::correrDerecha(){
  if( frameRight / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
    frameRight=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CORRERD,frameRight/RUNNING_ANIMATION_FRAMES);
  float vel = velocidad + 0.70;
  originX += vel;
}

void MovingSonic::correrIzquierda(){
  if( frameLeft / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
    frameLeft=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CORRERI,frameLeft/RUNNING_ANIMATION_FRAMES);
  float vel = (velocidad*-1) - 0.7;
  originX += vel;
}
