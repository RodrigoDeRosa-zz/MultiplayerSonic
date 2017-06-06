#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "CameraControl.hpp"
#include "../message.hpp"
#include "../Modelo/Player.hpp"
//#include "../Modelo/Modelo.hpp"
#include "../Modelo/Entidades/Entidad.hpp"

using namespace std;

class Control{
	int k;

	/*Modelo*/
	Modelo* modelo;
	/*Niveles*/
	int nivelActual;
	vector <Nivel*> niveles;

	/*Camara*/
	CameraControl* cameraControl;
	void setCameraPosition(float cameraPosition);
	bool moveCamera(float newPlayerX, string playerName, float dirX);

	void setDisconnectedPlayersPosition(float dirX);
	public:
		Control(gameMode game_mode);
		void initNiveles(gameMode);
		vector<float> getDirections(SDL_Event e, float dirX, float dirY);
		vector<float> getDirections(key_event e, string playerName);
		void addPlayer(string playerName);
		bool moveCameraAndPlayer(string playerName, vector<float> directions);
		vector<float> getPlayerPosition(string playerName);
		float getCameraPosition();
		void setPlayerConnection(string playerName, bool connection);
		void handleInMessage(in_message_t* ev);
		vector<out_message_t*> getStatus();
		void update();
		void crearEntidades(); //la idea es que esto reciba un .json y devuelva un vector de out_message_t*
		vector<out_message_t*> getEntidadesInitStatus();
};

#endif /*CONTROL_HPP*/
