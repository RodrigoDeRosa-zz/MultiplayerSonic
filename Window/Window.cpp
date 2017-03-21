#include "Stage.hpp"
#include "Window.hpp"
#include <string>
using namespace std;

/*Constructor*/
Window::Window(){
    width = 0;
    height = 0;
    stage = NULL;
}
/*Destructor, destruye el escenario si es que existe.*/
Window::~Window(){
    width = 0;
    height = 0;
    freeStage();
}
/*Define la altura de la ventana como el entero recibido*/
void Window::setWidth(int w){
    width = w;
}
/*Define el alto de la ventana como el entero reecibido*/
void Window::setHeight(int h){
    height = h;
}
/*Define el escenario de la ventana como el recibido*/
void Window::setFrontLayer(Stage* s){
    if (stage) delete stage;
    stage = s;
}
/*Destruye el escenario si es que existe*/
void Window::freeStage(void){
    if (stage){
        delete stage;
        stage = NULL;
    }
}
