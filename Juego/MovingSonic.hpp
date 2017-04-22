#ifndef MOVINGSONIC_HPP
#define MOVINGSONIC_HPP

#include "../Juego/MovingBloque.hpp"

using namespace std;

class MovingSonic: public MovingBloque{

  public:
    MovingSonic(int x, int y, int w, int h, int vel_s);
    /*Funciones de movimiento */
    void moveLeft(float);
    void moveRight(float);
    void moveLef(int frameL, int cantF, float vel ,int fact);

    void caminarDerecha(float);
    void caminarIzquierda(float);
    void correrDerecha(float);
    void correrIzquierda(float);

    void moveLeft(int, int, float ,int);

};

#endif /*MOVINGSONIC_HPP*/
