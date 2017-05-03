#include <SDL2/SDL.h>
#include <vector>
#include "../Modelo/Model.hpp"
#include "CameraControl.hpp"

using namespace std;

class Control{
	Model* model;
	CameraControl* cameraControl;
	void setCameraPosition(float cameraPosition);
	public:
		Control();
		void setPlayerPosition(string playerName, SDL_Event e);
		vector<float> handleEvent(string playerName,SDL_Event e);
		void addPlayer(string playerName);
		void movePlayerAndCamera(string playerName, SDL_Event e);
};
