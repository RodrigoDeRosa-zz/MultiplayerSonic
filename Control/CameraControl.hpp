#include "../Modelo/Model.hpp"

class CameraControl{
	float position;
	float width;
	bool playerOnLeftEdge;
	bool playerOnRightEdge;
	bool moveCameraLeft(float newPosition,Model* model);
	bool moveCameraRight(float newPosition,Model* model);
	public:
		CameraControl(float width);
		bool moveCamera(float newPosition, Model* model);
		float getLeftEdge();
		float getRightEdge();
		float getPosition();
};
