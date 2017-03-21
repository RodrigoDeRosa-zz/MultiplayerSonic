#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#ifndef CONTROLGRAFICO_H
#define CONTROLGRAFICO_H

bool init(SDL_Window* window , SDL_Renderer* renderer);
void close(SDL_Window* window , SDL_Renderer* renderer);

#endif
