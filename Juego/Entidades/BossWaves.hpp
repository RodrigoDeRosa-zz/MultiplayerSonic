#ifndef BOSS_WAVES_H
#define BOSS_WAVES_H

#include "../Entity.hpp"

class BossWaves: public Entity{
public:
    /*El alto y el ancho son siempre constantes, son defines del cpp*/
    BossWaves(float x, float y);
};

#endif //BOSS_WAVES_H
