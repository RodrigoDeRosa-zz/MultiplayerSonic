#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include "ModelSonic.hpp"
#include "Entidades/Entidad.hpp"
#include "../message.hpp"
#include <map>
#include <vector>

using namespace std;

class Player{
	string name;
	ModelSonic* sonic;
	bool connected;
    map <move_type, vector<float> > collitionBoxes;
	public:
		Player(string name);
		string getName();
		float getX();
		float getY();
		float getDirX();
		float getDirY();
		vector<float> getDirections();
		void setX(float x);
		void setY(float y);
		void setXY(float x, float y);
		void updateXY(float dirX, float dirY);
		bool isConnected();
		void setConnected(bool connected);
		move_type getMovement();
		int getFrame();
		void afectarseCon(Entidad* entidad);

		float getBordeDer();
		float getBordeIzq();
		float getBordeArriba();
		float getBordeAbajo();
		float getCentroX();
		float getCentroY();

		out_message_t* getStatus(float camPos);

		void cargarMapCollitionBoxes();

		void crouch();
		void charge();
		void release();
};

#endif /*PLAYER_HPP*/
