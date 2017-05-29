#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "MovingBloque.hpp"

class Entity: public MovingBloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Entity(float x, float y, float w, float h);
        void setFrame(int frame);
        void setFrame(int frame, int sense);
};

#endif /*ENTITY_HPP*/
