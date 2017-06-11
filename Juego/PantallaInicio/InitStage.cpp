#include "InitStage.hpp"
#include "../Buttons/Team1Button.hpp"
#include "../Buttons/Team2Button.hpp"

#define LOGO_MAX_FRAME 18
#define LOGO_FRAME_RATE 40

InitStage::InitStage(int w, int h, int type) : Stage(){
    setDimensions(w, h);

    logoFrame = 0;

    logo = new SonicLogo(w/2, -10);
    background = new Layer();
    background->setDimensions(w, h);

    if (type == 2){ //En caso de equipos
        //Layer
        background->setTexPath("Graficos/fondo_login_equipos.png");
        //Boton 1
        Texture* button1Tex = new Texture();
        button1Tex->loadFromFile("Graficos/boton_team1.png");
        textures.insert(make_pair("button1", button1Tex));
        Team1Button* button1 = new Team1Button(250, 500);
        button1->setTexture(button1Tex);
        buttons.push_back(button1);
        //Boton2
        Texture* button2Tex = new Texture();
        button2Tex->loadFromFile("Graficos/boton_team2.png");
        textures.insert(make_pair("button2", button2Tex));
        Team2Button* button2 = new Team2Button(785, 500);
        button2->setTexture(button2Tex);
        buttons.push_back(button2);
    } else { //Si es co-op o single
        //Layer
        background->setTexPath("Graficos/fondo_login.png");
        //Boton
        Texture* buttonTex = new Texture();
        buttonTex->loadFromFile("Graficos/boton_inicio.png");
        textures.insert(make_pair("button", buttonTex)); //Se guarda para asegurarse de borrarla desp
        StartButton* button = new StartButton(491, 440);
        button->setTexture(buttonTex);
        buttons.push_back(button);
    }

    Texture* logoTex = new Texture();
    logoTex->loadFromFile("Graficos/logoSonic.png");
    textures.insert(make_pair("logo", logoTex)); //Se guarda para asegurarse de borrarla desp
    logo->setTexture(logoTex);

    background->loadImage();
}

InitStage::~InitStage(){
    if (background){
        delete background;
        background = NULL;
    }
    for (int i = 0; i < buttons.size(); i++){
        delete buttons.at(i);
    }
    if (logo){
        delete logo;
        logo = NULL;
    }
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        delete it->second;
    }
}

key_event InitStage::processEvent(SDL_Event e){
    for (int i = 0; i < buttons.size(); i++){
        key_event key = buttons.at(i)->handleEvent(e);
        if (key != KEY_TOTAL) return key;
    }
    return KEY_TOTAL;
}

void InitStage::render(){
    background->render();

    logoFrame++;
    unsigned int frame = (logoFrame/LOGO_FRAME_RATE);
    frame = frame%4 + 10;
    logo->setFrame(frame);
    logo->render();

    for (int i = 0; i < buttons.size(); i++){
        buttons.at(i)->render();
    }
}

void InitStage::render(Camara* cam){
    render();
}
