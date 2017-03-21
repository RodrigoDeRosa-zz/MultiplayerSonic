#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#ifndef CONTROLGRAFICO_HPP
#define CONTROLGRAFICO_HPP

bool init(SDL_Window* window , SDL_Renderer* renderer);
void close(SDL_Window* window , SDL_Renderer* renderer);

#endif /*CONTROLGRAFICO_HPP*/
