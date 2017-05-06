#include "../Modelo/Model.hpp"

class CameraControl{
	float position;
	float width;
	bool playerOnLeftEdge;
	bool playerOnRightEdge;
	bool validNewPosition(float newPosition, Model* model);
	public:
		CameraControl(float width);
		bool moveCamera(float newPosition, Model* model);
		float getLeftEdge();
		float getRightEdge();
		float getPosition();
};
