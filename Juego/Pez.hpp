#ifndef PEZ_HPP
#define PEZ_HPP

#include "MovingBloque.hpp"

class Pez: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Pez(float x, float y);
};

#endif /*PEZ_HPP*/
