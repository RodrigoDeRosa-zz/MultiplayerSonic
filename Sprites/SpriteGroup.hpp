#pragma once
#include "Sprite.hpp"
#include <vector>

using namespace std;

class SpriteGroup
{
	vector <Sprite*> sprites; //vector de punteros a Sprite
	int sprites_size;
public:
	SpriteGroup();
	void add(Sprite * sprite);
	void remove(Sprite sprite);
	void update();
	void draw(SDL_Renderer * renderer);
	void empty();
	bool has(Sprite sprite);
	SpriteGroup copy();
};
