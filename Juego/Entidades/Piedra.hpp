#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "../../Graficos/Bloque.hpp"

class Piedra: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Piedra(float x, float y);
};

#endif /*PIEDRA_HPP*/
