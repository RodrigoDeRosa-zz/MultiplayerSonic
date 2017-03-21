#include "SpriteGroup.hpp"
#include "Sprite.hpp"
#include <vector>

using namespace std;

vector <Sprite*> sprites; //vector de punteros a Sprite

SpriteGroup::SpriteGroup()
{
}

void SpriteGroup::add(Sprite *sprite) {

	sprites.push_back(sprite);

}

void SpriteGroup::remove(Sprite sprite) {

	for (int i = 0; i < sprites_size; i++) {
		if (*sprites[i] == sprite) {
			sprites.erase(sprites.begin() + i);
		}
	}
}

void SpriteGroup::update() {

	if (!sprites.empty()) {
		for (int i = 0; i < (int)sprites.size(); i++) {
			(sprites[i])->update();
		}
	}
}

void SpriteGroup::draw(SDL_Renderer * renderer) {

	if (!sprites.empty()) {
		for (int i = 0; i < (int)sprites.size(); i++) {
			sprites[i]->draw(renderer);
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
