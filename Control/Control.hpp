#include <SDL2/SDL.h>
#include <vector>
#include "CameraControl.hpp"
#include "message.hpp"

using namespace std;

class Control{
	Model* model;
	CameraControl* cameraControl;
	void setCameraPosition(float cameraPosition);
	void setDisconnectedPlayersPosition(float dirX);
	bool moveCamera(float newPlayerX, string playerName);
	public:
		Control();
		vector<float> getDirections(SDL_Event e, float dirX, float dirY);
		vector<float> getDirections(key_event e, string playerName);
		void addPlayer(string playerName);
		bool moveCameraAndPlayer(string playerName, vector<float> directions);
		vector<float> getPlayerPosition(string playerName);
		float getCameraPosition();
		void setPlayerConnection(string playerName, bool connection);
		void handleInMessage(in_message_t* ev);
		vector<out_message_t*> getStatus();
		void update();
};
