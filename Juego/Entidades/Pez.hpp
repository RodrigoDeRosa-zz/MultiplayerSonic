#ifndef PEZ_HPP
#define PEZ_HPP

#include "../Entity.hpp"

class Pez: public Entity{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Pez(float x, float y);
};

#endif /*PEZ_HPP*/
