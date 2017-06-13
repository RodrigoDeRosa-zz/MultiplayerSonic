#include "Entity.hpp"
#include "../message.hpp"
#include <stdio.h>

Entity::Entity(float x, float y, float w, float h) : MovingBloque(x, y, w, h){
}

void Entity::setFrame(int frame){
    rectangle = clipsMovimientos->getRectangulo("move", frame);
}

void Entity::setFrame(int frame, move_type sense){
    if (sense == FLYL || sense == BOSSL) {
        rectangle = clipsMovimientos->getRectangulo("left", frame);
    } else if (sense == FLYD || sense == BOSSR){
        rectangle = clipsMovimientos->getRectangulo("right", frame);
    } else if (sense == FISHU){
        rectangle = clipsMovimientos->getRectangulo("up", frame);
    } else if (sense == FISHD){
        rectangle = clipsMovimientos->getRectangulo("down", frame);
    }
}
