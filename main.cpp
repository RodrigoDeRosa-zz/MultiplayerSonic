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
/*COSAS QUE FALTAN:
  -Circulo con color
  -Cropear circulo ancho y alto independientemente
  -Agregar path a los circulos(esta predefinido)*/
void initSeguido(camara* camara){
    Apuntado* seguido = new Apuntado(0, 0, 30, 30,3);
    Texture* invisible = new Texture();
    invisible->setKeyColor(0,0,0);
    seguido->setBackgroundColor(0, 0, 0);
    seguido->setTexture(invisible);
    camara->setApuntado(seguido);
}

int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("ejemplo.json");


    Stage* stage = json->getStage(); //DESCOMENTAR!

    bool running = true;
    SDL_Event e;

    //Parametros: iniX, iniY, velocidad, ancho, alto, ancho_escenario, alto escenario
    //int an_escenario=stage->getWidth();
    //int al_escenario=stage->getHeight();
    //camara* camara_pantalla = new camara(0,0,1,TAM,TAM,an_escenario, al_escenario );
    //initSeguido(camara_pantalla);
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
