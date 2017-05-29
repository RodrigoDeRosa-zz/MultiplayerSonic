#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "../MovingBloque.hpp"
#include "../ClipGroup.hpp"

class Piedra: public MovingBloque{
    private:
        int type; //Tipo de piedra
        ClipGroup* clips;
    public:
        /*El W y H dependen del tipo, se sobreescriben en la creacion*/
        Piedra(float x, float y, int t);
};

#endif /*PIEDRA_HPP*/
