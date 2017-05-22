#ifndef PINCHE_HPP
#define PINCHE_HPP

#include "../../Graficos/Bloque.hpp"

class Pinche: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Pinche(float x, float y);
};

#endif /*PINCHE_HPP*/
