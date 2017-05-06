#include <vector>
#include "Player.hpp"

using namespace std;

class Model{
	vector<Player*>* players;
	public:
		Model();
		void addPlayer(string playerName);
		Player* getPlayer(string name);
		void movePlayer(string playerName, float dirX, float dirY);
		void setPlayerPosition(string playerName, float x, float y);
		vector<float> getPlayerPosition(string playerName);
		bool playerInPosition(float position);
		void moveDisconnectedPlayers(float position);
		void setPlayerConnection(string playerName, bool connection);
};
