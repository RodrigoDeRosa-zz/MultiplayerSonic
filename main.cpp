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


int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger .
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("json/ejemplo.json");

    Stage* stage = json->getStage();

		Juego* juego = new Juego();
		juego->setStage(stage);
		Camara* camara_pantalla = json->getCamara();
		juego->setCamara(camara_pantalla);
		Jugadores* jugs = new Jugadores();
		juego->setJugadores(jugs);
		juego->setFactory();
		juego->addJugador("1","Sonic");
		//SegaFactory* factory = new SegaFactory();
		//Sonic* sonicc = factory -> getSonic("1");

    bool running = true;
    SDL_Event e;

		float velX = 0.0;
		float velY = 0.0;

		/*Estas son variables que se le pasan a los personajes,
		pero dentro de cada personaje sabe con que velocidad se tiene
		que mover. esta velocidad no es con la que se va a mover el
		jugador, sirve para saber para que lado se esta moviendo.

		---- velX > 0 implica que se mueve para la derecha.
		---- velY > 0 implica que salto.
		*/

		Control* control = new Control();
		control->addPlayer("1");
		float cameraPosition;
		vector<float> directions;

    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;}

						/*ESTO ES SUPER CABEZA PERO LO TIENE QUE MANEJAR EL
						SERVER, ES UN EJEMPLO DE COMO LO TIENE QUE HACER*/

            //sonic->setEventMovimiento(e);
						directions = control->getDirections(e,velX,velY);
						velX = directions[0];
						velY = directions[1];
						cameraPosition = control->getCameraPosition();
						}

				control->moveCameraAndPlayer("1",directions);


				juego->updateJugador("1", velX, velY, 0, 0, true);
				juego->updateCamara(cameraPosition,0);
				//printf("Velocidad sin dividir:%f \n",velX);

				//se le envia un string que dice que movimiento va a realizar

				//juego->updateJugador("0",velX,velY,0,0,0);
        //camara_pantalla->moveApuntado();
				//calcular mov camara con todos los personajes
				//camara_pantalla->moveCamara();

        //setea el color de fondo de blanco
        Renderer::getInstance().setDrawColor(255, 255, 255, 1);

        Renderer::getInstance().clear();
				juego->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
