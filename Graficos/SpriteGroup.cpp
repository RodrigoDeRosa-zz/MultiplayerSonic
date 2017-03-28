#include "SpriteGroup.hpp"
#include "Sprite.hpp"
#include <vector>
using namespace std;

SpriteGroup::SpriteGroup(){}
SpriteGroup::~SpriteGroup(){
    for (int i = 0; i < size; i++) {
		delete sprites[i];
	}
}

void SpriteGroup::add(Sprite* sprite){
    sprites.push_back(sprite);
}

void SpriteGroup::remove(Sprite sprite){
    for (int i = 0; i < size; i++) {
        if (*sprites[i] == sprite) {
            sprites.erase(sprites.begin() + i);
        }
    }
}

void SpriteGroup::update(){
    if (!sprites.empty()) {
        for (int i = 0; i < (int)sprites.size(); i++) {
            (sprites[i])->update();
        }
    }
}

void SpriteGroup::render(camara* camara){
    if (!sprites.empty()) {
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

Sprite* SpriteGroup::getSprite(string nombre) {

    for (int i = 0; i < (int)sprites.size(); i++) {
        if ((*sprites[i]).getID() == nombre) {
            return sprites[i];
        }
    }
    return NULL;
}

SpriteGroup SpriteGroup::copy() {

	SpriteGroup new_group;

	for (int i = 0; i < (int)sprites.size(); i++) {
		new_group.add(sprites[i]);
	}

	return new_group;
}
