#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Stage.hpp"
#include <string>
using namespace std;

/*Ventana principal del juego que es redimensionable y contiene el escenario.*/
class Window{
    private:
        int width;
        int height;
        Stage* stage;
    public:
        /*Define el ancho de la pantalla*/
        void setWidth(int);
        /*Define el alto de la pantalla*/
        void setHeight(int);
        /*Define el escenario de la pantalla*/
        void setStage(Stage*);
        /*Libera el escenario si es que existe*/
        void freeStage(void);
};

#endif //WINDOW_HPP
