#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include "../../Graficos/Bloque.hpp"

class Plataforma: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Plataforma(float x, float y);
};

#endif /*PLATAFORMA_HPP*/
