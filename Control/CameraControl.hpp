#include "../Modelo/Model.hpp"

class CameraControl{
	float position;
	float width;
	bool playerOnLeftEdge;
	bool playerOnRightEdge;
	float getLeftEdge();
	float getRightEdge();
	bool validNewPosition(float newPosition, Model* model);
	public:
		CameraControl(float width);
		bool moveCamera(float newPosition, Model* model);
};
