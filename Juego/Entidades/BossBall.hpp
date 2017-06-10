#ifndef TALLERSONIC_BOSSBALL_H
#define TALLERSONIC_BOSSBALL_H

#include "../../Graficos/Bloque.hpp"

class BossBall: public Bloque{
public:
    /*El alto y el ancho son siempre constantes, son defines del cpp*/
    BossBall(float x, float y);
};


#endif //TALLERSONIC_BOSSBALL_H
