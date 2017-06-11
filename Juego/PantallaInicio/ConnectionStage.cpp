#include "ConnectionStage.hpp"

#define LOGO_MAX_FRAME 18
#define LOGO_FRAME_RATE 40

ConnectionStage::ConnectionStage(int w, int h) : Stage(){
    setDimensions(w, h);

    //Layer
    background = new Layer();
    background->setDimensions(w, h);
    background->setTexPath("Graficos/fondo_login.png");
    background->loadImage();

    //Boton
    Texture* buttonTex = new Texture();
    buttonTex->loadFromFile("Graficos/boton_conectar.png");
    textures.insert(make_pair("button", buttonTex)); //Se guarda para asegurarse de borrarla desp
    button = new StartButton(491, 440);
    button->setTexture(buttonTex);

    logoFrame = 0;
    logo = new SonicLogo(w/2, -10);
    Texture* logoTex = new Texture();
    logoTex->loadFromFile("Graficos/logoSonic.png");
    textures.insert(make_pair("logo", logoTex)); //Se guarda para asegurarse de borrarla desp
    logo->setTexture(logoTex);
}

ConnectionStage::~ConnectionStage(){
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

key_event ConnectionStage::processEvent(SDL_Event e){
    button->handleEvent(e);
}

void ConnectionStage::render(){
    background->render();

    logoFrame++;
    unsigned int frame = (logoFrame/LOGO_FRAME_RATE);
    if (logoFrame/LOGO_FRAME_RATE > 13){
        frame = frame%4 + 10;
    }
    logo->setFrame(frame);
    logo->render();

    button->render();
}
