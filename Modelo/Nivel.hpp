#ifndef NIVEL_HPP
#define NIVEL_HPP

#include <vector>
#include "Player.hpp"

using namespace std;

class Nivel{
protected:
	vector<Player*>* players;
	vector<Entidad*>* entidades;
	int playerStatusControl;
	int entidadesStatusControl;
	gameMode modo_juego;
	vector<Puntaje*>* puntajes;
	bool changeLevelMessageSent;
	bool termino;
public:
		Nivel();

		void addPlayers( vector<Player*>* );
		void addPuntajes( vector<Puntaje*>* );
		void addEntidades( vector<Entidad*>* );

		void addEntidad(Entidad* entidad);
		Player* getPlayer(string name);
		virtual vector<string> getPlayerNames();
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
		vector<out_message_t*> getEntidadesInitStatus();
		void playerRoll(string playerName);
		virtual void colisionarTodos();
		bool enRango(Entidad* entidad, Player* player);
		vector<out_message_t*> getPlayerStatus(float camPos);
		vector<out_message_t*> getEntidadesStatus();
		virtual vector<out_message_t*> getStatus(float camPos);
		virtual void moverEntidades();
		void terminar();
		bool yaTermino();

};

#endif /*NIVEL_HPP*/
