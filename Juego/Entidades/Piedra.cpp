#include "Piedra.hpp"
#include <stdio.h>

#define HEIGHT 200

Piedra::Piedra(float x, float y, float w, float h, int t) : Bloque(x, y, w, h){
    type = t;
    clip = new Clip();
    if (type == 0){
        clip->addRectangulo(0, 0, 124, HEIGHT);
    } else if (type == 1){
        clip->addRectangulo(125, 0, 103, HEIGHT);
    } else {
        clip->addRectangulo(229, 0, 113, HEIGHT);
    }
    rectangle = clip->getRectangulo(0);
}
