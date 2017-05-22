#ifndef PIEDRA_HPP
#define PIEDRA_HPP

#include "../Graficos/Bloque.hpp"

class Piedra: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Piedra(float x, float y);
        /*
        Aca falta un metodo que actualice el frame del sprite porque las teles
        tienen animacion.
        */
};

#endif /*PIEDRA_HPP*/
