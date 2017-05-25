#include "MovingSonic.hpp"

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
#define WAITD "esperandoDer"
#define WAITI "esperandoIzq"
//#define BRAKED "frenoDer"
//#define BRAKEI "frenoIzq"
//#define BALLD "bolaDer"
//#define BALLI "bolaIzq"
#define DMGD "damageDer"
#define DMGI "damageIzq"
//#define CROUCHD "agachadoDer"
//#define CROUCHI "agachadoIzq"


MovingSonic::MovingSonic(float x, float y, int w, int h):
  MovingBloque(x,y,w,h){}

void MovingSonic::quietoDerecha(int frame){
  rectangle = clipsMovimientos->getRectangulo(QUIETOD,frame);
}

void MovingSonic::quietoIzquierda(int frame) {
  rectangle = clipsMovimientos->getRectangulo(QUIETOI,frame);
}

void MovingSonic::caminarDerecha(int frame){
  rectangle = clipsMovimientos->getRectangulo(CAMINARD,frame);
}

void MovingSonic::caminarIzquierda(int frame) {
  rectangle = clipsMovimientos->getRectangulo(CAMINARI,frame);
}

void MovingSonic::correrDerecha(int frame){
  rectangle = clipsMovimientos->getRectangulo(CORRERD,frame);
}

void MovingSonic::correrIzquierda(int frame) {
  rectangle = clipsMovimientos->getRectangulo(CORRERI,frame);
}

void MovingSonic::jumpDerecha(int frame){
  rectangle = clipsMovimientos->getRectangulo(SALTARD,frame);
}

void MovingSonic::jumpIzquierda(int frame){
  rectangle = clipsMovimientos->getRectangulo(SALTARI,frame);
}

void MovingSonic::damageDerecha(int frame) {
  rectangle = clipsMovimientos->getRectangulo(DMGD,frame);
}

void MovingSonic::damageIzquierda(int frame) {
  rectangle = clipsMovimientos->getRectangulo(DMGI,frame);
}

void MovingSonic::esperandoIzquierda(int frame) {
  rectangle = clipsMovimientos->getRectangulo(WAITI,frame);
}

void MovingSonic::esperandoDerecha(int frame) {
  rectangle = clipsMovimientos->getRectangulo(WAITD,frame);
}
