#include "Piedra.hpp"

/*Para pasarlo al creador de bloque*/
#define W 1000
#define H 200

Piedra::Piedra(float x, float y, int t) : MovingBloque(x, y, W, H){
    type = t;
    /*Se agregan todos los SDL_Rects de los 3 tipos*/
    setClip("piedra1");
    setRectangulo("piedra1", 0, 0, 124, 200);
    setClip("piedra2");
    setRectangulo("piedra2", 125, 0, 103, 200);
    setClip("piedra3");
    setRectangulo("piedra3", 229, 0, 113, 200);
    /*Se define el SDL_Rect segun el tipo*/
    switch (type) {
        case 0:
            rectangle = clipsMovimientos->getRectangulo("piedra1", 0); break;
        case 1:
            rectangle = clipsMovimientos->getRectangulo("piedra2", 0); break;
        case 2:
            rectangle = clipsMovimientos->getRectangulo("piedra3", 0); break;
    }
}
