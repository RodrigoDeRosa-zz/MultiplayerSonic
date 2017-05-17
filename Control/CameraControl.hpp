#include "../Modelo/Model.hpp"

class CameraControl{
	float position;
	float width;
	bool moveCameraLeft(float newPosition,Model* model, string playerName);
	bool moveCameraRight(float newPosition,Model* model, string playerName);
	bool playerInCameraRange(float playerPosition);
	public:
		CameraControl(float width);
		bool moveCamera(float newPosition, Model* model, string playerName, float dirX);
		float getPosition();
		float getLeftEdge();
		float getRightEdge();
};
