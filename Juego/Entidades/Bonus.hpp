#ifndef BONUS_HPP
#define BONUS_HPP

#include "../Entity.hpp"

class Bonus: public Entity{
    private:
        int type;
    public:
        /*El alto y el ancho son siempre constantes, son defines del cpp*/
        Bonus(float x, float y, int t);
};

#endif /*BONUS_HPP*/
