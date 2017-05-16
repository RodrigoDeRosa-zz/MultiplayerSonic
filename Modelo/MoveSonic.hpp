#ifndef TALLERSONIC_MODELSONIC_HPP
#define TALLERSONIC_MODELSONIC_HPP

using namespace std;

class ModelSonic{
    private:
        float originX;
        float originY;
        float width;
        float tiempoX;
        float tiempoY;
        float tiempoSalto;
        float frameRight;
        float frameLeft;
        float frameQuiet;
        float frameJumping;
        //La direccion se setea en true cuando esta para la derecha.
        float direccion;
        float jumping;
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

        void setPosicionInicio();
}

#endif //TALLERSONIC_MODELSONIC_HPP
