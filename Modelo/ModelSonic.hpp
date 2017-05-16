#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

using namespace std;

enum move_type{IDLE,JUMP,RUN,WALK,MOVE_TOTAL};

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
}

#endif //TALLERSONIC_MODELSONIC_HPP
