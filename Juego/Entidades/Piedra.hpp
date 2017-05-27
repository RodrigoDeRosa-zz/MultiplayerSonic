#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "../../Graficos/Bloque.hpp"
#include "../Clip.hpp"

class Piedra: public Bloque{
    private:
        int type; //Tipo de piedra
        Clip* clip;
    public:
        Piedra(float x, float y, float w, float h, int t);
};

#endif /*PIEDRA_HPP*/
