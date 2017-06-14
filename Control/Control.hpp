#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "CameraControl.hpp"
#include "../message.hpp"
#include "../Modelo/Player.hpp"
#include "../Modelo/Modelo.hpp"
#include "../Modelo/Transicion.hpp"
#include "../Modelo/Entidades/Entidad.hpp"
#include "../json/json/json.h"
#include "../json/json/json-forwards.h"

using namespace std;

class Control{
	int k;
	/*Modelo*/
	Modelo* modelo;

	/*Niveles*/
	int nivelActual;
	vector <Nivel*> niveles;

	bool terminado;

	/*Camara*/
	CameraControl* cameraControl;
	void setCameraPosition(float cameraPosition);
	bool moveCamera(float newPlayerX, string playerName, float dirX);
	Nivel* getNivelActual();
	void crearEntidades(string,Json::Value,int);

	void setDisconnectedPlayersPosition(float dirX);
	public:
		Control(gameMode game_mode);
		void initNiveles();
		gameMode getGameMode();
		vector<float> getDirections(SDL_Event e, float dirX, float dirY);
		vector<float> getDirections(key_event e, string playerName);
		void addPlayer(string playerName, int equipo);
		void cambiarEquipo(string playerName, int equipo);
		bool moveCameraAndPlayer(string playerName, vector<float> directions);
		vector<float> getPlayerPosition(string playerName);
		float getCameraPosition();
		void setPlayerConnection(string playerName, bool connection);
		void handleInMessage(in_message_t* ev);
		vector<out_message_t*> getStatus();
		void update();
		void crearEntidades(Json::Value);
		vector<out_message_t*> getEntidadesInitStatus();
		int getLevelNum();

		bool terminoElJuego();
};

#endif /*CONTROL_HPP*/
