#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "Player.hpp"
using namespace std;

class Model{
	vector<Player*>* players;
	vector<Entidad*>* entidades;
	int playerStatusControl;
	public:
		Model();
		void addPlayer(string playerName);
		void addEntidad(Entidad* entidad);
		Player* getPlayer(string name);
		vector<string> getPlayerNames();
		void movePlayer(string playerName, float dirX, float dirY);
		void setPlayerPosition(string playerName, float x);
		vector<float> getPlayerPosition(string playerName);
		vector<float> getPlayerDirections(string playerName);
		move_type getPlayerMovement(string playerName);
		int getPlayerFrame(string playerName);
		bool otherPlayerInPosition(string playerName,float position, bool left);
		void moveDisconnectedPlayers(float cameraLeftEdge,float cameraRightEdge,float dirX);
		void setPlayerConnection(string playerName, bool connection);
		vector<string> getDisconnectedPlayers();
		bool playerIsConnected(string playerName);
		void playerCrouch(string playerName);
		void playerCharge(string playerName);
		void playerRelease(string playerName);
		void colisionarTodos();
		bool enRango(Entidad* entidad, Player* player);
		vector<out_message_t*> getStatus(float camPos);
};

#endif /*MODEL_HPP*/
