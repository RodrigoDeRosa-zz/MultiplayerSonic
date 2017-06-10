#ifndef TALLERSONIC_BOSS_H
#define TALLERSONIC_BOSS_H

#include "../Entity.hpp"

class Boss: public Entity{
public:
    /*El alto y el ancho son siempre constantes, son defines del cpp*/
    Boss(float x, float y);
};

#endif //TALLERSONIC_BOSS_H
