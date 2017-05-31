#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

#include "MoveSonic.hpp"
#include <iostream>

//ojo que tienen que ser todos negativos!
#define NO_ARG -1.0
#define ROLL_ARG -2.0
#define DMG_ARG -3.0

using namespace std;

class ModelSonic{
private:

    MoveSonic* bloque_pers;
    int frameRight, frameLeft;
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
    void update(float,float,float = NO_ARG, float = NO_ARG);
    void setX(float);
    void setY(float);
    void cortarSalto();
    // setea direcciones en cero y llama a set posicion inicio
    void stop();
	void roll();	
	void lastimar();
/*
	void crouch();
	void release();
	void charge();
*/

};

#endif //TALLERSONIC_MODELSONIC_HPP
