#ifndef MONEDA_HPP
#define MONEDA_HPP

#include "../Graficos/Bloque.hpp"

class Moneda: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Moneda(float x, float y);
        /*
        Aca falta un metodo que actualice el frame del sprite porque las monedas giran
        */
};

#endif /*MONEDA_HPP*/
