#include <vector>
#include "Player.hpp"
#include "../Juego/SegaFactory.hpp"

using namespace std;

class Model{
	vector<Player*>* players;
	SegaFactory* segaFactory;
	public:
		Model();
		void addPlayer(string playerName);
		Player* getPlayer(string name);
		void movePlayer(string playerName, float dirX, float dirY);
		void setPlayerPosition(string playerName, float x, float y);
		vector<float> getPlayerPosition(string playerName);
		bool otherPlayerInPosition(string playerName,float position, bool left);
		void moveDisconnectedPlayers(float cameraLeftEdge,float cameraRightEdge,float dirX);
		void setPlayerConnection(string playerName, bool connection);
		vector<string> getDisconnectedPlayers();
		vector<float> getPlayerDirections(string playerName);
};
