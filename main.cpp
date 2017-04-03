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
/*FALTA:
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
//    Circulo* circulo1 = new Circulo(150, 300, 100);
//    Circulo* circulo2 = new Circulo(300, 150, 100);
    Bloque* bloque2 = new Bloque(100, 100, 100, 100);
    Bloque* bloque3 = new Bloque(Window::getInstance().getHeight()/2, Window::getInstance().getWidth()/2, 200, 200);

    /*El primero tiene textura*/
    bloque2->setTexture(tex);

    /*El tercero tiene color de fondo*/
    bloque3->setBackgroundColor(255,130,15);

    //el primer circulo tiene color de fondo
//    circulo1->setBackgroundColor(145, 143, 98);

    //el segundo circulo se le carga una imagen
//    SDL_Surface* aux_texture = IMG_Load("Graficos/index.png");
//    circulo2->setTexture(aux_texture);

    /*Se agregan al grupo de sprites*/
    SpriteGroup* activeSprites = new SpriteGroup();

    activeSprites->add(bloque2);

    /*Se define el sprite group del escenario como el creado recien*/
    stage->setSpriteGroup(activeSprites);
    /*Se agrega otro sprite al escenario*/
    stage->addSprite(bloque3);
//    stage->addSprite(circulo1);
//    stage->addSprite(circulo2);

    return stage;
}

int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("ejemplo.json");


    Stage* stage = json->getStage(); //DESCOMENTAR!
    //stage->setDimensiones(2*TAM, 2*TAM);

    //para probar
    //Stage* stage = setStage();
    //stage->setDimensiones(2*TAM, 2*TAM);

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
