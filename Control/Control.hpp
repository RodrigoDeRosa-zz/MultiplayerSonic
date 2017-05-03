#include <SDL2/SDL.h>
#include <vector>
#include "../Modelo/Model.hpp"

using namespace std;

class Control{
	Model* model;
	int cameraPosition;
	void setCameraPosition(float cameraPosition);
	public:
		Control();
		void setPlayerPosition(string playerName, SDL_Event e);
		vector<float> handleEvent(string playerName,SDL_Event e);
		void updateCamera(string playerName);
		void addPlayer(string playerName);
};
