#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "../MovingBloque.hpp"

class Moneda: public MovingBloque{
    private:
        int frame;
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Moneda(float x, float y);
        void incFrame();
        /* Este metodo muestra el ultimo frame y saca la moneda
        void desaparecer();
        */
};

#endif /*MONEDA_HPP*/
