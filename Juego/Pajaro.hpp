#ifndef PAJARO_HPP
#define PAJARO_HPP

#include "MovingBloque.hpp"

class Pajaro: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Pajaro(float x, float y);
};

#endif /*PAJARO_HPP*/
