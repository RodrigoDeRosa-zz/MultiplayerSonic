#include "SDL2/SDL.h"
#include <iostream>
#include "LTexture.h"

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

class Sprite {
	LTexture* get_texture();
protected:
	LTexture* texture;
	SDL_Rect rectangle;
	int origin_x, origin_y, width, height, r, g, b;
public:
	Sprite(int x, int y, int w, int h);
	void update();
	void draw(SDL_Renderer * destination);
	void set_texture(LTexture* new_texture);
	void set_background_color(int r, int g, int b);
	bool operator==(Sprite &other) const;
};

#endif
