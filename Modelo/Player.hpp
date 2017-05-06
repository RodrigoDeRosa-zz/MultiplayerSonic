#include <string>
#include "../Juego/Sonic.hpp"

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
	Sonic* sonic;
	public:
		Player(string name, Sonic* sonic);
		string getName();
		float getX();
		float getY();
		void setX(float x);
		void setY(float y);
		void updateXY(float dirX, float dirY);
		bool isConnected();
		void setConnected(bool connected);
};
