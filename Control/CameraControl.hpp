#include "../Modelo/Nivel.hpp"

class CameraControl{
	float position;
	float width;
	float stageEnd;
	bool moveCameraLeft(float newPosition,Nivel* model, string playerName);
	bool moveCameraRight(float newPosition,Nivel* model, string playerName);
	bool playerInCameraRange(float playerPosition);
	public:
		CameraControl(float width, float stageEnd);
		bool moveCamera(float newPosition, Nivel* model, string playerName, float dirX);
		float getPosition();
		float getLeftEdge();
		float getRightEdge();
};
