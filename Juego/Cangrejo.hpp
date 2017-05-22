#ifndef CANGREJO_HPP
#define CANGREJO_HPP

#include "MovingBloque.hpp"

class Cangrejo: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Cangrejo(float x, float y);
};

#endif /*CANGREJO_HPP*/
