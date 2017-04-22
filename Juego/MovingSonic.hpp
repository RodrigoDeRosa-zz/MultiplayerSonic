#ifndef MOVINGSONIC_HPP
#define MOVINGSONIC_HPP

#include "../Juego/MovingBloque.hpp"

using namespace std;

class MovingSonic: public MovingBloque{

  public:
    MovingSonic(int x, int y, int w, int h, int vel_s);
    /*Funciones de movimiento */
    void moveRight(int, int, float, int);
    void moveLeft(int, int, float, int);
    void caminarDerecha(float);
    void correrDerecha(float);
    void caminarIzquierda(float);
    void correrIzquierda(float);

};

#endif /*MOVINGSONIC_HPP*/
