#include "Bonus.hpp"

#define WIDTH 300
#define HEIGHT 120
#define W 100
#define H 120

Bonus::Bonus(float x, float y, int t) : Entity(x, y, WIDTH, HEIGHT){
    type = t;
    /*Se agregan todos los SDL_Rects de los 3 tipos*/
    setClip("moneda");
    setRectangulo("moneda", 0, 0, W, H);
    setClip("invencib");
    setRectangulo("invencib", 100, 0, W, H);
    setClip("escudo");
    setRectangulo("escudo", 200, 0, W, H);
    /*Se define el SDL_Rect segun el tipo*/
    switch (type) {
        case 0:
            rectangle = clipsMovimientos->getRectangulo("moneda", 0); break;
        case 1:
            rectangle = clipsMovimientos->getRectangulo("invencib", 0); break;
        case 2:
            rectangle = clipsMovimientos->getRectangulo("escudo", 0); break;
    }
}
