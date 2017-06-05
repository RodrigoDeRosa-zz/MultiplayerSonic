#ifndef INVENCIBLE_HPP
#define INVENCIBLE_HPP

#include "../Entity.hpp"

class Invencibilidad: public Entity{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Invencibilidad(float x, float y);
};

#endif /*INVENCIBLE_HPP*/
