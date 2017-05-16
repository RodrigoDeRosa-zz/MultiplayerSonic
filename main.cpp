#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Camara.hpp"
#include "Juego/Juego.hpp"
#include "json/JsonLoader.hpp"
#include "Juego/SegaFactory.hpp"
#include "Juego/Sonic.hpp"
#include "Logger2.hpp"
#include "Control/Control.hpp"
#include <SDL2/SDL.h>
#include <string>

#define DEFAULT_JSON "json/ejemplo2.json"


int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger .
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("json/ejemplo.json", DEFAULT_JSON);
    json->setGame();/*
    Stage* stage = json->getStage();

	Juego* juego = new Juego();
	juego->setStage(stage);
	Camara* camara_pantalla = json->getCamara(stage);
	juego->setCamara(camara_pantalla);
	Jugadores* jugs = new Jugadores();
	juego->setJugadores(jugs);
	juego->setFactory();
	juego->addJugador("1","Sonic");
	juego->addJugador("2","Sonic");

    bool running = true;
    SDL_Event e;

	float velX = 0.0;
	float velY = 0.0;
	Control* control = new Control();
	control->addPlayer("1");
	control->addPlayer("2");
	control->setPlayerConnection("2",false);
	float cameraPosition;
	vector<float> directions;

    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;}
			directions = control->getDirections(e,velX,velY);
			velX = directions[0];
			velY = directions[1];
		}
		float auxVelX = velX;
		float auxVelY = velY;
		if(!(control->moveCameraAndPlayer("1",directions))){
				auxVelX = 0;
				auxVelY = 0;
		}
		cameraPosition = control->getCameraPosition();
		juego->updateJugador("1", auxVelX, auxVelY, 0, 0, true);
		juego->updateJugador("2",0,0,control->getPlayerPosition("2")[0],300,false);
		juego->updateCamara(cameraPosition,0);
        //setea el color de fondo de blanco
        Renderer::getInstance().setDrawColor(255, 255, 255, 1);
        Renderer::getInstance().clear();
		juego->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();
*/
    return 0;
}
