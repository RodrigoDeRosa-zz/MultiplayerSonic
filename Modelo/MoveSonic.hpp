#ifndef TALLERSONIC_MOVESONIC_HPP
#define TALLERSONIC_MOVESONIC_HPP

#include "../message.hpp"

using namespace std;

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
		unsigned int charges;
		unsigned int noActionCounter;
		unsigned int cont_roll;
        //La direccion se setea en true cuando esta para la derecha.
        bool direccion;
        bool jumping;
		bool rolling;
        int frameActual;
        move_type moveActual;
    public:
        MoveSonic(float x, float y);
        /*Funciones de movimiento */
        void moveLeft(float);
        void moveRight(float);
        void jump(float,float);
		void roll();
        void caminarDerecha();
        void caminarIzquierda();
        void correrDerecha();
        void correrIzquierda();
        void jumpDerecha(float*);
        void jumpIzquierda(float*);
		void frenarDerecha();
		void frenarIzquierda();
		void agacharseDerecha();
		void agacharseIzquierda();
		void decrementarVelocidad();

        void update(float, float);
        bool estaSaltando();
		bool estaRodando();

        int getX();
        int getY();

        int getFrame();
        move_type getMovement();

        void setPosicionInicio();
        void setX(float);
        void setY(float);
};

#endif //TALLERSONIC_MOVESONIC_HPP
