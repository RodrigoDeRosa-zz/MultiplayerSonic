#include "InitStage.hpp"

InitStage::InitStage(int w, int h) : Stage(){
    setDimensions(w, h);

    button = new StartButton(w/2, h - (4*h)/5);
    logo = new SonicLogo(w/2, h - h/4);
    background = new Layer();
    background->setDimensions(w, h);

    Texture* buttonTex = new Texture();
    buttonTex->loadFromFile("Graficos/boton_inicio.png");
    textures.insert(make_pair("button", buttonTex)); //Se guarda para asegurarse de borrarla desp
    button->setTexture(buttonTex);

    Texture* logoTex = new Texture();
    logoTex->loadFromFile("Graficos/logoSonic.png");
    textures.insert(make_pair("logo", logoTex)); //Se guarda para asegurarse de borrarla desp
    logo->setTexture(logoTex);

    background->setTexPath("Graficos/fondo_login.png");
    background->loadImage();
}

InitStage::~InitStage(){
    if (background){
        delete background;
        background = NULL;
    }
    if (button){
        delete button;
        button = NULL;
    }
    if (logo){
        delete logo;
        logo = NULL;
    }
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        delete it->second;
    }
}

void InitStage::render(){
    button->render();
    logo->render();
    background->render();
}
