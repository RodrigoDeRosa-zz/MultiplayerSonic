#include "TransitionStageCoop.hpp"
#include <sstream>
#include <string>
#include <SDL2/SDL_ttf.h>

TransitionStageCoop::TransitionStageCoop(int w, int h) : TransitionStage(w, h){
    background->setTexPath("Graficos/fondo_Tras_Colaborativo.png");
    background->loadImage();

    for (int i = 0; i < 3; i++){
        coopInfo.push_back(0);
    }
}

void TransitionStageCoop::setValues(){
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
            case 1: x = 465; break;
            case 2: x = 715; break;
            case 3: x = 966; break;
            default: x = 220; break;
        }
        sprite = new Sprite(x, 422, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i), texture));
        text.push_back(sprite);
    }
    for (int i = 0; i < 3; i++){
        texture = new Texture();
        texture->loadFromRenderedText(font, to_string(coopInfo.at(i)), color);
        int x = 365;
        switch (i) {
            case 1: x = 548; break;
            case 2: x = 788; break;
        }
        sprite = new Sprite(x, 557, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i+4), texture));
        text.push_back(sprite);
    }
    TTF_CloseFont(font);
}

void TransitionStageCoop::setCoopInfo(int rings, int points, int total){
    coopInfo[0] = rings;
    coopInfo[1] = points;
    coopInfo[2] = total;
}
