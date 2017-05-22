#include "SpriteGroup.hpp"
#include "Sprite.hpp"
#include <vector>
#include <algorithm>
using namespace std;

SpriteGroup::SpriteGroup(){}
SpriteGroup::~SpriteGroup(){
    for (int i = 0; i < (int)sprites.size(); i++) {
        if(sprites[i]) delete sprites[i];
	}
}

void SpriteGroup::add(Sprite* sprite){
    sprites.push_back(sprite);
}

void SpriteGroup::remove(Sprite sprite){
    for (int i = 0; i < (int)sprites.size(); i++) {
        if (*sprites[i] == sprite) {
            sprites.erase(sprites.begin() + i);
        }
    }
}

void SpriteGroup::update(int index,float new_x, float new_y){
    if (index >= sprites.size()){
        printf("SpriteGroup::update | index %d fuera de rango!\n", index);
        return;
    }
    sprites[index]->update(new_x, new_y);
}


/*Funcion de ordenamiento del array de sprites*/
struct order{
    inline bool operator() (Sprite* sprite1, Sprite* sprite2){
        return ( sprite1->getZIndex() < sprite2->getZIndex());
    }
};

void SpriteGroup::render(Camara* camara){
    if (!sprites.empty()) {
        std::sort(sprites.begin(), sprites.end(), order());
        for (int i = 0; i < (int)sprites.size(); i++) {
            sprites[i]->render(camara);
        }
    }
}

void SpriteGroup::empty() {
	sprites.clear();
}

bool SpriteGroup::has(Sprite sprite) {

	for (int i = 0; i < (int)sprites.size(); i++) {
		if (*sprites[i] == sprite) {
			return true;
		}
	}
	return false;
}

SpriteGroup SpriteGroup::copy() {

	SpriteGroup new_group;

	for (int i = 0; i < (int)sprites.size(); i++) {
		new_group.add(sprites[i]);
	}

	return new_group;
}

vector <Sprite*> SpriteGroup::getSprites(){
  return sprites;
}
