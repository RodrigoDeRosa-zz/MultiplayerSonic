#ifndef SONICLOGO_HPP
#define SONICLOGO_HPP

#include "../Entity.hpp"

class SonicLogo : public Entity{
    public:
        SonicLogo(int x, int y);
        void render();
};

#endif /*SONICLOGO_HPP*/
