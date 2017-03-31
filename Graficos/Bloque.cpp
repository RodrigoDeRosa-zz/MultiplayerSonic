#include "Sprite.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Bloque.hpp"

Bloque::Bloque(int x, int y, int w, int h)
: Sprite(x, y, w, h){
}