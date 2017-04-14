#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Layer.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Sprite.hpp"
#include "Graficos/Apuntado.hpp"
#include "Graficos/SpriteGroup.hpp"
#include "Graficos/Camara.hpp"
#include "Graficos/Bloque.hpp"
#include "Graficos/Circulo.hpp"
#include "JsonLoader.hpp"
#include "Logger2.hpp"
#include <SDL2/SDL.h>

const int TAM = 600;

int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("ejemplo.json");


    Stage* stage = json->getStage();

    bool running = true;
    SDL_Event e;

	camara* camara_pantalla = json->getCamara();
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
        stage->render(camara_pantalla);
        camara_pantalla->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
