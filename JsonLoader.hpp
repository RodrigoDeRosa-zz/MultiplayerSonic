#include <SDL2/SDL.h>
#include "Sprites/SpriteGroup.hpp"


using namespace std;

class JsonLoader{
	SDL_Window* ventana;
	SpriteGroup sprites;
	public:
		JsonLoader(char* ruta);
		SDL_Window* obtener_ventana();
		SpriteGroup obtener_sprites();
};
