#ifndef TALLERSONIC_MOVESONIC_HPP
#define TALLERSONIC_MOVESONIC_HPP

using namespace std;

enum move_type{IDLED, IDLEI, JUMPD, JUMPI, RUND, RUNI, WALKD, WALKI, MOVE_TOTAL};

class MoveSonic{
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
        bool direccion;
        bool jumping;
        int frameActual;
        move_type moveActual;
    public:
        MoveSonic(float x, float y);
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

        void update(float, float);
        bool estaSaltando();

        int getX();
        int getY();

        int getFrame();
        move_type getMovement();

        void setPosicionInicio();
};

#endif //TALLERSONIC_MOVESONIC_HPP
