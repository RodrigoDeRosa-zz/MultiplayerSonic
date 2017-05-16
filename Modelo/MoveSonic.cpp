#include "ModelSonic.h"

#include "ModelSonic.hpp"

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
/*MOVIMIENTOS*/
#define QUIETOD "quietoDer"
#define QUIETOI "quietoIzq"
#define CAMINARD "caminarDer"
#define CAMINARI "caminarIzq"
#define CORRERD "correrDer"
#define CORRERI "correrIzq"
#define SALTARD "saltarDer"
#define SALTARI "saltarIzq"

ModelSonic::ModelSonic(float x, float y){
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
    //La direccion se setea en true cuando esta para la derecha.
    direccion = true;
    jumping = false;
}

void ModelSonic::setPosicionInicio(){
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
    if(direccion){
        //rectangle = clipsMovimientos->getRectangulo(QUIETOD,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
    }
    else{
        //rectangle = clipsMovimientos->getRectangulo(QUIETOI,frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
    }
    frameQuiet++;
}

void ModelSonic::jump(float vel_x,float vel_y){

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

    //if(direccion){rectangle = clipsMovimientos->getRectangulo(SALTARD,(frameJumping)/(4*JUMPING_ANIMATION_FRAMES));}
    //if(not direccion){rectangle = clipsMovimientos->getRectangulo(SALTARI,(frameJumping)/(4*JUMPING_ANIMATION_FRAMES));}

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

void ModelSonic::jumpDerecha(float* velH){
    direccion = true;
    *velH = VELOCIDAD*5;
    if(tiempoX >= CONTROL_CAMINATA){
        *velH += RUN*2;
    }
    //rectangle = clipsMovimientos->getRectangulo(SALTARD,(frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void ModelSonic::jumpIzquierda(float* velH){
    direccion = false;
    *velH = VELOCIDAD*(-5);
    if(tiempoX <= -CONTROL_CAMINATA){
        *velH -= RUN*2;
    }
    //rectangle = clipsMovimientos->getRectangulo(SALTARI,(frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    if( originX < 0 ){originX = 0;}
}


void ModelSonic::moveRight(float vel_x){

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

void ModelSonic::moveLeft(float vel_x){
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

void ModelSonic::caminarDerecha(){
    if( frameRight / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameRight=0;
    }
    //rectangle = clipsMovimientos->getRectangulo(CAMINARD,frameRight/WALKING_ANIMATION_FRAMES);
    originX += VELOCIDAD;
}

void ModelSonic::caminarIzquierda(){
    if( frameLeft / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    //rectangle = clipsMovimientos->getRectangulo(CAMINARI,frameLeft/WALKING_ANIMATION_FRAMES);
    originX -= VELOCIDAD;
}

void ModelSonic::correrDerecha(){
    if( frameRight / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameRight=0;
    }
    //rectangle = clipsMovimientos->getRectangulo(CORRERD,frameRight/RUNNING_ANIMATION_FRAMES);
    float vel = VELOCIDAD + RUN;
    originX += vel;
}

void ModelSonic::correrIzquierda(){
    if( frameLeft / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    //rectangle = clipsMovimientos->getRectangulo(CORRERI,frameLeft/RUNNING_ANIMATION_FRAMES);
    float vel = (VELOCIDAD*-1) - RUN;
    originX += vel;
}
