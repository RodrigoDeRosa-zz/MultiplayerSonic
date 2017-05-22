#ifndef BONUS_HPP
#define BONUS_HPP

#include "../../Graficos/Bloque.hpp"

class Bonus: public Bloque{
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Bonus(float x, float y);
        /*
        Aca falta un metodo que actualice el frame del sprite porque las teles
        tienen animacion.
        */
};

#endif /*BONUS_HPP*/
