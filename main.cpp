#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Layer.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Sprite.hpp"
#include "Graficos/SpriteGroup.hpp"
#include <SDL2/SDL.h>

Stage* setStage(){
    Stage* stage = new Stage();
    /*Capa frontal*/
    Layer* front = new Layer();
    front->setTexPath("Graficos/front.png");
    front->loadImage();
    front->setIndexZ(99);
    /*Capa de fondo*/
    Layer* back = new Layer();
    back->setTexPath("Graficos/back.png");
    back->loadImage();
    back->setIndexZ(98);

    stage->addLayer(front);
    stage->addLayer(back);

    /*Se crea la textura de los sprites*/
    Texture* tex = new Texture();
    tex->loadFromFile("Graficos/texture.png");
    /*Se crean tres sprites*/
    Sprite* bloque1 = new Sprite(0, 0, 100, 100);
    Sprite* bloque2 = new Sprite(150, 150, 100, 100);
    Sprite* bloque3 = new Sprite(Window::getInstance().getHeight()/2, Window::getInstance().getWidth()/2, 200, 200);
    /*Dos tienen textura*/
    bloque1->setTexture(tex);
    bloque2->setTexture(tex);
    /*El tercero tiene color de fondo*/
    bloque3->setBackgroundColor(255,130,15);

    /*Se agregan al grupo de sprites*/
    SpriteGroup* activeSprites = new SpriteGroup();
    activeSprites->add(bloque1);
    activeSprites->add(bloque2);

    /*Se define el sprite group del escenario como el creado recien*/
    stage->setSpriteGroup(activeSprites);
    /*Se agrega otro sprite al escenario*/
    stage->addSprite(bloque3);

    return stage;
}

int main(int argc, char** argv){
    SDLHandler::getInstance().init();

    Window::getInstance().setDimensions(860, 640);
    Window::getInstance().init();

    Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);

    Stage* stage = setStage();

    bool running = true;
    SDL_Event e;
    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) running = false;
        }
        Renderer::getInstance().clear();
        stage->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
