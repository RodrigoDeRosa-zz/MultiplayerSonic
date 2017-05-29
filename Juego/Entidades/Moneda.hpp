#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "../MovingBloque.hpp"
#include "../../Graficos/Camara.hpp"

class Moneda: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Moneda(float x, float y);
        /*frame = 4 es desaparecer*/
        void render(Camara*);
};

#endif /*MONEDA_HPP*/
