#include "MovingSonic.hpp"
#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640
#define CONTROL_MOVIMIENTO 0.001
#define CONTROL_CAMINATA 1.0


MovingSonic::MovingSonic(int x, int y, int w, int h, int vel_s):
  MovingBloque(x,y,w,h, vel_s){
  }

void MovingSonic::moveRight(int frame, int cant_frames, float vel_x, int fact){

    //Si la velocidad era menor a 0, se movia para la izquierda.
    if(velX<0.0){
      velX = 0.0;
    }
    //Actualizamos el control de movimiento
    velX += CONTROL_MOVIMIENTO;

    //esto tiene que ir dentro de la funcion caminar y correr, con cada frame correspondiente.
    rectangle.x = frame/(fact*cant_frames) * rectangle.w;

    if (velX<CONTROL_CAMINATA){caminarDerecha(vel_x);}
    else if(velX>=CONTROL_CAMINATA){correrDerecha(vel_x);}

    if( originX + width > ANCHO_ESCENARIO ){ originX = ANCHO_ESCENARIO - width;}
}

void MovingSonic::caminarDerecha(float vel_x){
  originX += vel_x;
}

void MovingSonic::correrDerecha(float vel_x){
  vel_x += 0.50;
  originX += vel_x;
}

void MovingSonic::moveLeft(int frame, int cant_frames, float vel_x, int fact){
    //Si la velocidad era mayor a 0, se movia para la derecha
    if(velX >0.0){
      velX = 0.0;
    }
    //Actualizamos el control de movimiento.
    velX -= CONTROL_MOVIMIENTO;

    //Esto tiene que ir dentro de la funcion caminar y correr con cada frame correspondiente.
    rectangle.x = ((frame / (cant_frames+1)) * rectangle.w);

    if(velX > -CONTROL_CAMINATA){caminarIzquierda(vel_x);}
    else if(velX <= -CONTROL_CAMINATA){correrIzquierda(vel_x);}

    if( originX < 0 ){ originX = 0; }
}

void MovingSonic::caminarIzquierda(float vel_x){
  originX += vel_x;
}

void MovingSonic::correrIzquierda(float vel_x){
  vel_x -= 0.5;
  originX += vel_x;
}
