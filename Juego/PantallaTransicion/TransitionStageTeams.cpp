#include "TransitionStageTeams.hpp"
#include <sstream>
#include <string>
#include <SDL2/SDL_ttf.h>

TransitionStageTeams::TransitionStageTeams(int w, int h) : TransitionStage(w, h){
    background->setTexPath("Graficos/fondo_Tras_Equipos.png");
    background->loadImage();

    /*Se crea un vector [rings, pints, total] para cada jugador*/
    for (int i = 0; i < 4; i++){
        vector<int> info;
        info.push_back(0); //rings
        info.push_back(0); //points
        info.push_back(0); //total
        teamInfo.push_back(info);
    }
}

void TransitionStageTeams::setValues(){
    Texture* texture;
    Sprite* sprite;
    TTF_Font* font = TTF_OpenFont("Graficos/fontTrans.ttf", 40); //Se inicializa la fuente
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    for (int i = 0; i < 4; i++){
        /*Rings*/
        texture = new Texture();
        texture->loadFromRenderedText(font, to_string(playerInfo.at(i).at(0)), color);
        int x;
        switch (i) {
            case 1: x = 466; break;
            case 2: x = 717; break;
            case 3: x = 968; break;
            default: x = 215; break;
        }
        sprite = new Sprite(x, 424, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i), texture));
        text.push_back(sprite);
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            texture = new Texture();
            texture->loadFromRenderedText(font, to_string(teamInfo[i][j]), color);
            int x = 161;
            switch (j) {
                case 1: x = 292; break;
                case 2: x = 487; break;
            }
            sprite = new Sprite(x + i*508, 612, 104, 40);
            sprite->setTexture(texture);
            textures.insert(make_pair(to_string(j+(i+1)*4), texture));
            text.push_back(sprite);
        }
    }
    TTF_CloseFont(font);
}

void TransitionStageTeams::setTeamInfo(int team, int rings, int points, int total){
    teamInfo[team][0] = rings;
    teamInfo[team][1] = points;
    teamInfo[team][2] = total;
}
