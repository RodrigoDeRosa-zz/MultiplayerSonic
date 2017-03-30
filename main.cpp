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
#include "JsonLoader.hpp"

#include <SDL2/SDL.h>

const int TAM = 600;

void initSeguido(camara* camara){
    Apuntado* seguido = new Apuntado(0, 0, 30, 30,3);
    Texture* invisible = new Texture();
    invisible->setKeyColor(0,0,0);
    seguido->setBackgroundColor(0, 0, 0);
    seguido->setTexture(invisible);
    camara->setApuntado(seguido);
}

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

    /*Se crean 2 sprites*/
    Sprite* bloque2 = new Sprite(150, 150, 100, 100);
    Sprite* bloque3 = new Sprite(Window::getInstance().getHeight()/2, Window::getInstance().getWidth()/2, 200, 200);

    /*El primero tiene textura*/

    bloque2->setTexture(tex);
    /*El tercero tiene color de fondo*/
    bloque3->setBackgroundColor(255,130,15);

    /*Se agregan al grupo de sprites*/
    SpriteGroup* activeSprites = new SpriteGroup();

    activeSprites->add(bloque2);

    /*Se define el sprite group del escenario como el creado recien*/
    stage->setSpriteGroup(activeSprites);
    /*Se agrega otro sprite al escenario*/
    stage->addSprite(bloque3);

    return stage;
}

int main(int argc, char** argv){
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("ejemplo.json");

    Stage* stage = json->getStage();
    stage->setDimensiones(2*TAM, 2*TAM);

    bool running = true;
    SDL_Event e;

    //Parametros: iniX, iniY, velocidad, ancho, alto, ancho_escenario, alto escenario
    int an_escenario=stage->getWidth();
    int al_escenario=stage->getHeight();
    camara* camara_pantalla = new camara(0,0,1,TAM,TAM,an_escenario, al_escenario );
    initSeguido(camara_pantalla);

    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;}
            camara_pantalla->setEventApuntado(e);
        }
        /*recordatorio: aca tiene que pasarse como parametros 2 veces el tam
        despues ver bien el tema de los layers y eso*/
        camara_pantalla->moveApuntado(2*TAM,2*TAM);
        camara_pantalla->moveCamara();

        Renderer::getInstance().clear();
        stage->render(camara_pantalla);
        camara_pantalla->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
