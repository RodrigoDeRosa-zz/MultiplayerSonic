#include "Stage.hpp"
#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "../logger/current/Logger2.hpp"
#include <map>
#include <string>
using namespace std;

Stage::Stage(){
    sprites = NULL;
    front = NULL;
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
    if(sprites){
        delete sprites;
        sprites = NULL;
    }
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
    if(!front->getTexture()){
        delete front;
        front = NULL;
        Layer* defaultFront = new Layer();
        defaultFront->setTexPath("Graficos/defaultFront.png");
        defaultFront->setDimensions(width, height);
        defaultFront->loadImage();
        front = defaultFront;
    }
    if(!background->getTexture()){
        delete background;
        background = NULL;
        Layer* defaultBackground = new Layer();
        defaultBackground->setTexPath("Graficos/defaultBackground.png");
        defaultBackground->setDimensions(width, height);
        defaultBackground->loadImage();
        background = defaultBackground;
    }
    background->render(camara);
    front->render(camara);
    /*Recorre todos los SpriteGroups y los renderiza*/
    for (map<string, SpriteGroup*>::iterator it = spriteGroups.begin(); it != spriteGroups.end(); it++){
        it->second->render(camara); //it->second es el valor, es decir, el spriteGroup
    }
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

/*Nuevo*/
void Stage::addSprite(string groupKey, Sprite* sprite){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->add(sprite); //Se añade el sprite
}

void Stage::updateSprite(string groupKey, int index, float x, float y){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->update(index, x, y); //Le pasa la tarea al grupo.
}

void Stage::updateSprite(string groupKey, int index, float x, float y, int frame){
    SpriteGroup* group = getSpriteGroup(groupKey);
    if (!group){
        printf("Grupo %s no encontrado!\n", groupKey);
        return;
    }
    group->update(index, x, y, frame); //Le pasa la tarea al grupo.
}

void Stage::removeSprite(string groupKey, int index){
    SpriteGroup* group = getSpriteGroup(groupKey);
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
