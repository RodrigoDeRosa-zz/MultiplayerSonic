#include "Bonus.hpp"

#define WIDTH 70
#define HEIGHT 70

Bonus::Bonus(float x, float y, int t) : Entity(x, y, WIDTH, HEIGHT){
    type = t;
    /*Se agregan todos los SDL_Rects de los 3 tipos*/
    setClip("bonus1");
    setRectangulo("bonus1", 0, 0, 124, 200);
    setClip("bonus2");
    setRectangulo("bonus2", 125, 0, 103, 200);
    setClip("bonus3");
    setRectangulo("bonus3", 229, 0, 113, 200);
    /*Se define el SDL_Rect segun el tipo*/
    switch (type) {
        case 0:
            rectangle = clipsMovimientos->getRectangulo("bonus1", 0); break;
        case 1:
            rectangle = clipsMovimientos->getRectangulo("bonus2", 0); break;
        case 2:
            rectangle = clipsMovimientos->getRectangulo("bonus3", 0); break;
    }
}
