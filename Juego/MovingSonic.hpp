#ifndef MOVINGSONIC_HPP
#define MOVINGSONIC_HPP

#include "../Juego/MovingBloque.hpp"

using namespace std;

class MovingSonic: public MovingBloque{

  public:
    MovingSonic(float x, float y, int w, int h);
    /*Funciones de movimiento */
    void moveLeft(float);
    void moveRight(float);
    void jump(float,float);

    void caminarDerecha();
    void caminarIzquierda();
    void correrDerecha();
    void correrIzquierda();
    void jumpDerecha(float*);
    void jumpIzquierda(float*);

    void setPosicionInicio();

};

#endif /*MOVINGSONIC_HPP*/
