#include "MoveSonic.hpp"
#include "../message.hpp"

/*DIMENSIONES ESCENARIO*/
#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640
/*CONSTANTES*/
#define CONTROL_MOVIMIENTO 0.001
#define CONTROL_CAMINATA 1.0
#define CONTROL_SALTO 0.0001
#define FACTOR 12
/*MOVIMIENTOS*/
#define GRAVEDAD 0.5
#define SALTO -12.0
#define VELOCIDAD 0.35
#define RUN 0.7
/*FRAMES*/
#define WALKING_ANIMATION_FRAMES 14
#define RUNNING_ANIMATION_FRAMES 8
#define JUMPING_ANIMATION_FRAMES 5
#define QUIET_ANIMATION_FRAMES 7

MoveSonic::MoveSonic(float x, float y){
    originX = x;
    originY = y;
    width = 117;
    tiempoX=0.0;
    tiempoY=0.0;
    tiempoSalto=0.0;
    frameRight = 0;
    frameLeft = 0;
    frameQuiet = 0;
    frameJumping = 0;
    frameActual = 0;
    //La direccion se setea en true cuando esta para la derecha.
    direccion = true;
    jumping = false;
}

void MoveSonic::setPosicionInicio(){
    tiempoX = 0.0;
    tiempoY = 0.0;
    tiempoSalto = 0.0;
    frameLeft=0;
    frameRight=0;
    frameJumping=0;
    jumping = false;

    if( frameQuiet / (FACTOR*QUIET_ANIMATION_FRAMES) >= QUIET_ANIMATION_FRAMES){
        frameQuiet=0;
    }
    //si esta apuntando para la derecha
    frameActual = (frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
    if(direccion){
        moveActual = IDLED;
    }
    else{
        moveActual = IDLEI;
    }
    frameQuiet++;
}

void MoveSonic::jump(float vel_x,float vel_y){

    if( frameJumping / (4*JUMPING_ANIMATION_FRAMES) >= JUMPING_ANIMATION_FRAMES){
        frameJumping=0;
    }

    if(tiempoY == 0 && not jumping){
        tiempoY = SALTO;
        jumping = true;
    }

    float velH = 0;
    if(vel_x>0){
        jumpDerecha(&velH);
    }
    if(vel_x<0){
        jumpIzquierda(&velH);
    }

    frameActual = (frameJumping)/(4*JUMPING_ANIMATION_FRAMES);
    if(direccion){moveActual = JUMPD;}
    if(not direccion){moveActual = JUMPI;}

    originX += 3*(velH * tiempoSalto);
    originY += 2*(tiempoY * tiempoSalto);
    tiempoY += (GRAVEDAD * tiempoSalto);

    tiempoSalto += CONTROL_MOVIMIENTO;
    frameJumping ++;

    //Este chequeo se hace para que vuelva a empezar de 0 el salto.
    if(tiempoY >= (SALTO*-1) && jumping){
        tiempoSalto = 0.0;
        jumping = false;
        tiempoY = 0.0;
    }

}

void MoveSonic::jumpDerecha(float* velH){
    direccion = true;
    *velH = VELOCIDAD*5;
    if(tiempoX >= CONTROL_CAMINATA){
        *velH += RUN*2;
    }
    frameActual = ((frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    moveActual = JUMPD;
    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void MoveSonic::jumpIzquierda(float* velH){
    direccion = false;
    *velH = VELOCIDAD*(-5);
    if(tiempoX <= -CONTROL_CAMINATA){
        *velH -= RUN*2;
    }
    frameActual = ((frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    moveActual = JUMPI;
    if( originX < 0 ){originX = 0;}
}


void MoveSonic::moveRight(float vel_x){

    //Si la VELOCIDAD era menor a 0, se movia para la izquierda.
    if(tiempoX <= 0.0){
        jumping =false;
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

void MoveSonic::moveLeft(float vel_x){
    //Si la VELOCIDAD era mayor a 0, se movia para la derecha
    if(tiempoX >= 0.0){
        jumping =false;
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

void MoveSonic::caminarDerecha(){
    if( frameRight / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameRight=0;
    }
    frameActual = (frameRight/WALKING_ANIMATION_FRAMES);
    moveActual = WALKD;
    originX += VELOCIDAD;
}

void MoveSonic::caminarIzquierda(){
    if( frameLeft / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    frameActual = (frameLeft/WALKING_ANIMATION_FRAMES);
    moveActual = WALKI;
    originX -= VELOCIDAD;
}

void MoveSonic::correrDerecha(){
    if( frameRight / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameRight=0;
    }
    frameActual = (frameRight/RUNNING_ANIMATION_FRAMES);
    moveActual = RUND;
    float vel = VELOCIDAD + RUN;
    originX += vel;
}

void MoveSonic::correrIzquierda(){
    if( frameLeft / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    frameActual = (frameLeft/RUNNING_ANIMATION_FRAMES);
    moveActual = RUNI;
    float vel = (VELOCIDAD*-1) - RUN;
    originX += vel;
}

int MoveSonic::getFrame(){
    return frameActual;
}

move_type MoveSonic::getMovement(){
    return moveActual;
}

void MoveSonic::update(float new_x, float new_y){
    originX = new_x;
    originY = new_y;
}

bool MoveSonic::estaSaltando(){
    return jumping;
}

int MoveSonic::getX(){
    return originX;
}

int MoveSonic::getY(){
    return originY;
}

void MoveSonic::setX(float new_x){
    originX = new_x;
}
