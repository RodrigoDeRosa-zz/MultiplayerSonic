#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

using namespace std;

enum move_type{IDLED, IDLEI, JUMPD, JUMPI, RUND, RUNI, WALKD, WALKI, MOVE_TOTAL};

class ModelSonic{
    private:
        float originX;
        float originY;
        float width;
        float tiempoX;
        float tiempoY;
        float tiempoSalto;
        int frameRight;
        int frameLeft;
        int frameQuiet;
        int frameJumping;
        //La direccion se setea en true cuando esta para la derecha.
        float direccion;
        float jumping;
        int frameActual;
        move_type moveActual;
    public:
        ModelSonic(float x, float y);
        /*Funciones de movimiento */
        void moveLeft(float);
        void moveRight(float);
        void jump(float,float);

        void caminarDerecha();
        void caminarIzquierda();
        void correrDerecha();
        void correrIzquierda();
        void jumpDerecha(float*);
        void jumpIzquierda(float*);

        int getFrame();
        move_type getMovement();

        void setPosicionInicio();
}

#endif //TALLERSONIC_MODELSONIC_HPP
