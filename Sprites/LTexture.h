/*
 * LTexture.h
 *
 *  Created on: Mar 16, 2017
 *      Author: marc
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#ifndef LTEXTURE_H_
#define LTEXTURE_H_

using namespace std;

class LTexture {
	SDL_Texture* get_texture()
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
public:
	LTexture();
	bool loadFromFile( string path, SDL_Renderer* gRenderer );
	void free();
	void render( int x, int y, SDL_Renderer* gRenderer );
	void set_background_color(Uint8 r, Uint8 g, Uint8 b)
	int getWidth();
	int getHeight();
	bool operator==(const LTexture &other) const
	~LTexture();
};

#endif /* LTEXTURE_H_ */
