#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include "ModelSonic.hpp"
#include "Entidades/Entidad.hpp"
#include "../message.hpp"
#include <map>
#include <vector>
#include "Puntaje.hpp"
#include "Estado/Estado.hpp"

using namespace std;

class Player{
	string name;
	ModelSonic* sonic;
	bool connected;
	int monedas;
	int vidas;
    map <move_type, vector<float> > collitionBoxes;
	Puntaje* puntaje;
	Estado* estado;
	public:
		Player(string name, Puntaje* p);
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
		int getVidas();
		int getMonedas();

		void setEstado(state_type estado);
		state_type getEstado();

		void agregarMonedas(int n);
		void quitarMonedas();

		void quitarVida();

		bool estaAtacando();
		bool estaSaltando();

		bool enRangoX(Entidad* entidad);
		bool enRangoY(Entidad* entidad);
		void afectarseCon(Entidad* entidad);

		bool recibirGolpe();

		float getBordeDer();
		float getBordeIzq();
		float getBordeArriba();
		float getBordeAbajo();
		float getCentroX();
		float getCentroY();

		out_message_t* getStatus(float camPos);

		void cargarMapCollitionBoxes();
		void roll();
		void lastimar();
		void caer();

		void sumarPuntos(int puntos);
		long getPuntos();

		void cambiarEquipo(Puntaje* newp);
};

#endif /*PLAYER_HPP*/
