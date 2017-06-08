#include "InitStage.hpp"
#include <stdio.h>
#include <math.h>

#define LOGO_MAX_FRAME 10
#define LOGO_FRAME_RATE 40

InitStage::InitStage(int w, int h) : Stage(){
    setDimensions(w, h);

    logoFrame = 0;

    button = new StartButton(w/2, (3*h)/4 - 50);
    logo = new SonicLogo(w/2, h/10);
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
    background->render();

    logoFrame++;
    unsigned int frame = (logoFrame/LOGO_FRAME_RATE) % LOGO_MAX_FRAME;
    logo->setFrame(frame);
    logo->render();

    button->render();
}
