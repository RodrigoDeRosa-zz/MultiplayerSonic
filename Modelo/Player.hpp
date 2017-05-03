#include <string>

using namespace std;

class Player{
	string name;
	float x;
	float y;
	float velX;
	float velY;
	public:
		Player(string name);
		string getName();
		float getX();
		float getY();
		void setX(float x);
		void setY(float y);
		void setVelX(float velX);
		void setVelY(float velY);
		float getVelX();
		float getVelY();
		void updateX(float velX);
		void updateY(float velY);
		void updateXY(float velX, float velY);
};
