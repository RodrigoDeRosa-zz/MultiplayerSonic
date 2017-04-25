#include "MovingSonic.hpp"
#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640
#define CONTROL_MOVIMIENTO 0.001
#define CONTROL_CAMINATA 1.0
#define WALKING_ANIMATION_FRAMES 14
#define RUNNING_ANIMATION_FRAMES 8
#define JUMPING_ANIMATION_FRAMES 6
#define QUIET_ANIMATION_FRAMES 7

#define CORRERD "correrDer"
#define CORRERI "correrIzq"
#define CAMINARD "caminarDer"
#define CAMINARI "caminarIzq"
#define QUIETOD "quietoDer"
#define QUIETOI "quietoIzq"
#define FACTOR 12

MovingSonic::MovingSonic(int x, int y, int w, int h, int vel_s):
  MovingBloque(x,y,w,h, vel_s){
  }

void MovingSonic::jump(float vel_x,float vel_y){
  //
  // if( frameQuiet / (FACTOR*QUIET_ANIMATION_FRAMES) >= QUIET_ANIMATION_FRAMES){
  //   frameQuiet=0;
  // }
  // if(direccion){
  //   rectangle = clipsMovimientos->getRectangulo(QUIETOD,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
  // }
  // else{
  //   rectangle = clipsMovimientos->getRectangulo(QUIETOI,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
  // }
  // frameQuiet++;
  //
  // originX += vel_x*frame;
  // originY += vel_y*frame;
  // vel_y+= gravedad*frame;
}

void MovingSonic::setPosicionInicio(){
    velX = 0.0;
    velY = 0.0;
    frameLeft=0;
    frameRight=0;

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

void MovingSonic::moveRight(float vel_x){

    //Si la velocidad era menor a 0, se movia para la izquierda.
    if(velX <= 0.0){
      direccion = true;
      frameLeft = 0;
      frameQuiet=0;
      velX = 0.0;
    }
    //Actualizamos el control de movimiento
    velX += CONTROL_MOVIMIENTO;

    if (velX<CONTROL_CAMINATA){caminarDerecha(vel_x);}
    else if(velX>=CONTROL_CAMINATA){correrDerecha(vel_x);}

    //Actualizamos el frame
    frameRight++;

    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void MovingSonic::moveLeft(float vel_x){
  //Si la velocidad era mayor a 0, se movia para la derecha
  if(velX >= 0.0){
    direccion = false;
    frameRight =0;
    frameQuiet=0;
    velX = 0.0;
  }
  //Actualizamos el control de movimiento.
  velX -= CONTROL_MOVIMIENTO;

  if(velX > -CONTROL_CAMINATA){caminarIzquierda(vel_x);}
  else if(velX <= -CONTROL_CAMINATA){correrIzquierda(vel_x);}

  //actualizamos el frame
  frameLeft++;

  if( originX < 0 ){originX = 0;}
}

void MovingSonic::caminarDerecha(float vel_x){
  if( frameRight / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
    frameRight=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CAMINARD,frameRight/WALKING_ANIMATION_FRAMES);
  originX += vel_x;
}

void MovingSonic::caminarIzquierda(float vel_x){
  if( frameLeft / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
    frameLeft=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CAMINARI,frameLeft/WALKING_ANIMATION_FRAMES);
  originX += vel_x;
}

void MovingSonic::correrDerecha(float vel_x){
  if( frameRight / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
    frameRight=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CORRERD,frameRight/RUNNING_ANIMATION_FRAMES);
  vel_x += 0.70;
  originX += vel_x;
}

void MovingSonic::correrIzquierda(float vel_x){
  if( frameLeft / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
    frameLeft=0;
  }
  rectangle = clipsMovimientos->getRectangulo(CORRERI,frameLeft/RUNNING_ANIMATION_FRAMES);
  vel_x -= 0.7;
  originX += vel_x;
}
