#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

#include "MoveSonic.hpp"

using namespace std;

class ModelSonic{
private:
    float originX;
    float originY;
    float direccionX;
    float direccionY;
    bool running;
    bool jumping;


public:
    void setMoveSonic(MoveSonic*);
    void moveRight(float);
    void moveLeft(float);
    void jump();
    int getFrame();
    move_type getMovement();
    float getX();
    float getY();
    float getDirX();
    float getDirY();
    void update(float,float,float,float);
};

#endif //TALLERSONIC_MODELSONIC_HPP
