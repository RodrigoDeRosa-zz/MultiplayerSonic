#include <SDL2/SDL.h>


using namespace std;

class JsonLoader{
	SDL_Window* ventana;
	public:
		JsonLoader(char* ruta);
		SDL_Window* obtener_ventana();
};
