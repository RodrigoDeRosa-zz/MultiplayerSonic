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
#include <SDL2/SDL.h>

const int TAM = 600;

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

    Texture* invisible = new Texture();
    invisible->loadFromFile("Graficos/dot.bmp");
    /*Se crean tres sprites*/
    Sprite* bloque1 = new Sprite(0, 0, 30, 30,"bloque1");
    Sprite* bloque2 = new Sprite(150, 150, 100, 100, "bloque2");
    Sprite* bloque3 = new Sprite(Window::getInstance().getHeight()/2, Window::getInstance().getWidth()/2, 200, 200, "bloque3");
    /*Dos tienen textura*/
    bloque1->setTexture(invisible);
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

    Window::getInstance().setDimensions(TAM, TAM);
    Window::getInstance().setDimensionesEscenario(2*TAM, 2*TAM);
    Window::getInstance().init();

    Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);

    Stage* stage = setStage();

    bool running = true;
    SDL_Event e;
    
    SpriteGroup* sprites = stage->getSprites();
    Sprite* sprite_movimiento = sprites->getSprite("bloque1");
    if (sprite_movimiento==NULL){
        //Levantar error de que no lo encontro
    }

    //Parametros: iniX, iniY, velocidad, ancho, alto, ancho_escenario, alto escenario
    int an_escenario=Window::getInstance().getWidthEscenario();
    int al_escenario=Window::getInstance().getHeightEscenario();
    camara* camara_pantalla = new camara(0,0,20,TAM,TAM,an_escenario, al_escenario );
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
