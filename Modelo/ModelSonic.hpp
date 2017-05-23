#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

#include "MoveSonic.hpp"
#include <iostream>

using namespace std;

class ModelSonic{
private:

    MoveSonic* bloque_pers;
    int frameRight, frameLeft;
	int space_was_down;
    float direccionX, direccionY;

public:
    ModelSonic();
    void moveRight(float);
    void moveLeft(float);
    void jump(float, float);
    int getFrame();
    move_type getMovement();
    float getX();
    float getY();
    float getDirX();
    float getDirY();
    void update(float,float,float = -1.0, float = -1.0);
    void setX(float);
    void setY(float);
    // setea direcciones en cero y llama a set posicion inicio
    void stop();

	void crouch();
	void release();
	void charge();
};

#endif //TALLERSONIC_MODELSONIC_HPP
