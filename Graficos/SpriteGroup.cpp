#include "SpriteGroup.hpp"
#include "Sprite.hpp"
#include <vector>
#include <algorithm>
using namespace std;

SpriteGroup::SpriteGroup(){}
SpriteGroup::~SpriteGroup(){
    for (map<int, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
        if (it->second){
            delete it->second;
        }
    }
}

void SpriteGroup::add(Sprite* sprite){
    sprites.insert(make_pair(sprites.size(), sprite));
}

void SpriteGroup::remove(Sprite sprite){
    for (map<int, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
        if ( *(it->second) == sprite){
            sprites.erase(it);
            return;
        }
    }
}

void SpriteGroup::remove(int index){
    sprites.erase(index);
}

void SpriteGroup::update(int index, float new_x, float new_y){
    if (index >= sprites.size()){
        printf("SpriteGroup::update | index %d fuera de rango!\n", index);
        return;
    }
    map<int, Sprite*>::iterator it;
    it = sprites.find(index);
    Sprite* sprite = it->second;
    sprite->update(new_x, new_y);
}

void SpriteGroup::update(int index, float new_x, float new_y, int frame){
    if (index >= sprites.size()){
        printf("SpriteGroup::update | index %d fuera de rango!\n", index);
        return;
    }
    map<int, Sprite*>::iterator it;
    it = sprites.find(index);
    Sprite* sprite = it->second;
    sprite->setFrame(frame);
    sprite->update(new_x, new_y);
}


/*Funcion de ordenamiento del array de sprites*/
struct order{
    inline bool operator() (Sprite* sprite1, Sprite* sprite2){
        return ( sprite1->getZIndex() < sprite2->getZIndex());
    }
};

void SpriteGroup::render(Camara* camara){
    if (!sprites.empty()) {
        vector<Sprite*> s;
        for (map<int, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
            s.push_back(it->second);
        }
        std::sort(s.begin(), s.end(), order());
        for (int i = 0; i < (int)s.size(); i++) {
            s[i]->render(camara);
        }
    }
}

void SpriteGroup::empty() {
	sprites.clear();
}

bool SpriteGroup::has(Sprite sprite) {
    for (map<int, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
        if ( *(it->second) == sprite){
            return true;
        }
    }
    return false;
}

map<int, Sprite*> SpriteGroup::getSprites(){
  return sprites;
}
