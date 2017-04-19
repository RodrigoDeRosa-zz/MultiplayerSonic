#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Camara.hpp"
#include "Juego/Juego.hpp"
#include "json/JsonLoader.hpp"
#include "Juego/SegaFactory.hpp"
#include "Juego/Sonic.hpp"
#include "Logger2.hpp"
#include <SDL2/SDL.h>


int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("json/ejemplo.json");

    Stage* stage = json->getStage();

		Juego* juego = new Juego();
		juego->setStage(stage);
		Camara* camara_pantalla = json->getCamara();
		juego->setCamara(camara_pantalla);
		//juego->addJugador("facu","sonic");

    bool running = true;
    SDL_Event e;

    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;}
            camara_pantalla->setEventApuntado(e);
        }

        camara_pantalla->moveApuntado();
        camara_pantalla->moveCamara();

        //setea el color de fondo de blanco
        Renderer::getInstance().setDrawColor(255, 255, 255, 1);

        Renderer::getInstance().clear();
        juego->render();
        //camara_pantalla->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
