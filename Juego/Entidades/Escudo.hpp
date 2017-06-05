#ifndef ESCUDO_HPP
#define ESCUDO_HPP

#include "../Entity.hpp"

class Escudo: public Entity{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Escudo(float x, float y);
};

#endif /*ESCUDO_HPP*/
