#include <string>

using namespace std;

class Player{
	string name;
	float x;
	float y;
	float vel;
	int eventCounterX;
	int eventCounterY;
	int eventCounterJump;
	bool jumping;
	bool connected;
	void moveX(float dirX);
	void jumpLeft(float* velH);
	void jumpRight(float* velH);
	public:
		Player(string name);
		string getName();
		float getX();
		float getY();
		void setX(float x);
		void setY(float y);
		void stop();
		void updateXY(float dirX, float dirY);
		void jump(float dirX);
		bool isConnected();
		void setConnected(bool connected);
};
