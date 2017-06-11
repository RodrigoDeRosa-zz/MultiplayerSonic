#include "Stage.hpp"
#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "../logger/current/Logger2.hpp"
#include <map>
#include <string>
using namespace std;

Stage::Stage(){
    front = NULL;
    score = NULL;
    background = NULL;
    width=0;
    height=0;
}

Stage::~Stage(){
    if (front){
        delete front;
        front = NULL;
    }
    if (background){
        delete background;
        background = NULL;
    }
    if (score){
        delete score;
        score = NULL;
    }
}

void Stage::render(){
    //virtual
}

key_event Stage::processEvent(SDL_Event e){
    //Virtual
}

void Stage::setDimensions(int w, int h){
    width = w;
    height = h;
}

int Stage::getWidth(){
    return width;
}

int Stage::getHeight(){
    return height;
}

void Stage::addLayer(Layer* layer){
    /*Si ya se tienen ambas capas no se pueden agregar mas*/
    if (front && background){
	    Logger::getInstance().log("In Stage::addLayer(): Stage already has two layers!",ALTO);
        return;
    }
    /*Si no habia ninguna capa se define la de adelante*/
    if (!front){
        front = layer;
    }else{
        /*Si habia una capa se verifica cual de las dos es la del frente.*/
        if (*layer <= *front){
            background = layer;
        } else{
            background = front;
            front = layer;
        }
    }
}

void Stage::render(Camara* camara){
    if (background) background->render(camara);
    if (front) front->render(camara);
    /*Recorre todos los SpriteGroups y los renderiza*/
    for (map<string, SpriteGroup*>::iterator it = spriteGroups.begin(); it != spriteGroups.end(); it++){
        it->second->render(camara); //it->second es el valor, es decir, el spriteGroup
    }
    for (map<string, EntityGroup*>::iterator it = entityGroups.begin(); it != entityGroups.end(); it++){
        it->second->render(camara); //it->second es el valor, es decir, el entityGroup
    }
    if (score) score->render();
}

/*Nuevo*/
void Stage::addSpriteGroup(string key, SpriteGroup* group){
    spriteGroups.insert(make_pair(key, group));
}
/*Nuevo v0.2*/
void Stage::addSpriteGroup(string key){
    SpriteGroup* group = new SpriteGroup();
    spriteGroups.insert(make_pair(key, group));
}

void Stage::addEntityGroup(string key){
    EntityGroup* group = new EntityGroup();
    entityGroups.insert(make_pair(key, group));
}

SpriteGroup* Stage::getSpriteGroup(string groupKey){
    map<string, SpriteGroup*>::iterator it;
    it = spriteGroups.find(groupKey);
    if (it == spriteGroups.end()){
        //Si no existe el grupo, no hace nada
        printf("Sprite group %s no existe!\n", groupKey);
        return NULL;
    }
    return it->second; //Se agarra el valor de la clave.
}

EntityGroup* Stage::getEntityGroup(string groupKey){
    map<string, EntityGroup*>::iterator it;
    it = entityGroups.find(groupKey);
    if (it == entityGroups.end()){
        //Si no existe el grupo, no hace nada
        printf("EntityGroup %s no existe!\n", groupKey);
        return NULL;
    }
    return it->second; //Se agarra el valor de la clave.
}

/*Nuevo*/
void Stage::initScore(int mode){
    score = new ScoreController(mode);
}

void Stage::addSprite(string groupKey, Sprite* sprite, int index){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->add(sprite, index); //Se añade el sprite
}

void Stage::addEntity(string groupKey, Entity* entity, int index){
    EntityGroup* group = getEntityGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->add(entity, index); //Se añade el sprite
}

void Stage::updateSprite(string groupKey, int index, float x, float y){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->update(index, x, y); //Le pasa la tarea al grupo.
}

void Stage::updateEntity(string groupKey, int index, float x, float y, int frame){
    EntityGroup* group = getEntityGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->update(index, x, y, frame); //Le pasa la tarea al grupo.
}

void Stage::updateEntity(string groupKey, int index, float x, float y, int frame, move_type sense){
    EntityGroup* group = getEntityGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->update(index, x, y, frame, sense); //Le pasa la tarea al grupo.
}

void Stage::updateScore(int index, int rings, int lives, int points, bool state){
    score->update(index, rings, lives, points, state);
}

void Stage::removeSprite(string groupKey, int index){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->remove(index); //Le pasa la tarea al grupo.
}

void Stage::removeEntity(string groupKey, int index){
    EntityGroup* group = getEntityGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->remove(index); //Le pasa la tarea al grupo.
}

Stage& Stage::getInstance(){
    static Stage instance;
    return instance;
}
