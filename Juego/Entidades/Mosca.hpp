#ifndef PAJARO_HPP
#define PAJARO_HPP

#include "../MovingBloque.hpp"

class Mosca: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Mosca(float x, float y);
};

#endif /*PAJARO_HPP*/
