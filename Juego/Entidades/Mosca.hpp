#ifndef PAJARO_HPP
#define PAJARO_HPP

#include "../Entity.hpp"

class Mosca: public Entity{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Mosca(float x, float y);
};

#endif /*PAJARO_HPP*/
