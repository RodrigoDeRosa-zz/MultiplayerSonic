#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Layer.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Sprite.hpp"
#include "Graficos/SpriteGroup.hpp"
#include "Graficos/Punto.hpp"
#include "Graficos/Camara.hpp"
#include "JsonLoader.hpp"
#include <SDL2/SDL.h>

int main(int argc, char** argv){
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("ejemplo.json");

    Stage* stage = json->getStage();

    bool running = true;
    SDL_Event e;
    
    SpriteGroup* sprites = stage->getSprites();
    Sprite* sprite_movimiento = sprites->getSprite("bloque1");
    if (sprite_movimiento==NULL){
        //Levantar error de que no lo encontro
    }

    camara* camara_pantalla = new camara(0,0,20,600,600);
    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;
            }
           sprite_movimiento->handleEvent(e);
        }
        sprite_movimiento->move();
        camara_pantalla->moveCamara(sprite_movimiento);
        
        Renderer::getInstance().clear();
        stage->render(camara_pantalla);
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
