#include "TransitionStage.hpp"

#define LOGO_MAX_FRAME 18
#define LOGO_FRAME_RATE 20

TransitionStage::TransitionStage(int w, int h) : Stage(){
    setDimensions(w, h);

    logoFrame = 0;

    /*Se crea un vector [rings, pints, total] para cada jugador*/
    for (int i = 0; i < 4; i++){
        vector<int> info;
        info.push_back(0); //rings
        info.push_back(0); //points
        info.push_back(0); //total
        playerInfo.push_back(info);
    }

    logo = new SonicSmallLogo(20, 0);
    background = new Layer();
    background->setDimensions(w, h);

    Texture* logoTex = new Texture();
    logoTex->loadFromFile("Graficos/logoSonicChico.png");
    textures.insert(make_pair("logo", logoTex)); //Se guarda para asegurarse de borrarla desp
    logo->setTexture(logoTex);
}

TransitionStage::~TransitionStage(){
    if (background){
        delete background;
        background = NULL;
    }
    for (int i = 0; i < text.size(); i++){
        delete text.at(i);
    }
    if (logo){
        delete logo;
        logo = NULL;
    }
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        delete it->second;
    }
}

void TransitionStage::setPlayerInfo(int player, int rings, int points, int total){
    playerInfo[player][0] = rings;
    playerInfo[player][1] = points;
    playerInfo[player][2] = total;
}

void TransitionStage::setValues(){
    //Virtual
}

void TransitionStage::render(){
    background->render();

    logoFrame++;
    unsigned int frame = (logoFrame/LOGO_FRAME_RATE);
    if (logoFrame/LOGO_FRAME_RATE > 13){
        frame = frame%4 + 10;
    }
    logo->setFrame(frame);
    logo->render();

    for (int i = 0; i < text.size(); i++){
        text.at(i)->render();
    }
}

void TransitionStage::render(Camara* cam){
    render();
}
