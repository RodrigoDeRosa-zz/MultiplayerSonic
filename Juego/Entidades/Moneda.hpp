#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "../Entity.hpp"

class Moneda: public Entity{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Moneda(float x, float y);
        /*frame = 4 es desaparecer*/
};

#endif /*MONEDA_HPP*/
