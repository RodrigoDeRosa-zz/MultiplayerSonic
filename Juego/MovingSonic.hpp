#ifndef MOVINGSONIC_HPP
#define MOVINGSONIC_HPP

#include "../Juego/MovingBloque.hpp"

using namespace std;

class MovingSonic: public MovingBloque{

  public:
    MovingSonic(float x, float y, int w, int h);
    /*Funciones de movimiento */

    void quietoDerecha(int);
    void quietoIzquierda(int);
    void caminarDerecha(int);
    void caminarIzquierda(int);
    void correrDerecha(int);
    void correrIzquierda(int);
    void jumpDerecha(int);
    void jumpIzquierda(int);
    void damageDerecha(int);
    void damageIzquierda(int);
    void esperandoDerecha(int);
    void esperandoIzquierda(int);

};

#endif /*MOVINGSONIC_HPP*/
