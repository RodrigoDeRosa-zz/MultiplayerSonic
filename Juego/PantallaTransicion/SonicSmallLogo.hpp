#ifndef SONICSMALLLOGO_HPP
#define SONICSMALLLOGO_HPP

#include "../Entity.hpp"

class SonicSmallLogo : public Entity{
    public:
        SonicSmallLogo(int x, int y);
        void render();
};

#endif /*SONICSMALLLOGO_HPP*/
