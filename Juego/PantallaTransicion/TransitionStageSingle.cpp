#include "TransitionStageSingle.hpp"
#include <sstream>
#include <string>
#include <SDL2/SDL_ttf.h>

TransitionStageSingle::TransitionStageSingle(int w, int h) : TransitionStage(w, h){
    background->setTexPath("Graficos/fondo_Tras.png");
    background->loadImage();
}

void TransitionStageSingle::setValues(){
    Texture* texture;
    Sprite* sprite;
    text.clear();
    TTF_Font* font = TTF_OpenFont("Graficos/fontTrans.ttf", 40); //Se inicializa la fuente
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    for (int i = 0; i < 4; i++){
        /*Rings*/
        texture = new Texture();
        texture->loadFromRenderedText(font, to_string(playerInfo.at(i).at(0)), color);
        sprite = new Sprite(225 + i*250, 425, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i+1), texture));
        text.push_back(sprite);
        /*Points*/
        texture = new Texture();
        texture->loadFromRenderedText(font, to_string(playerInfo.at(i).at(1)), color);
        sprite = new Sprite(225 + i*250, 490, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i+2), texture));
        text.push_back(sprite);
        /*Total*/
        texture = new Texture();
        texture->loadFromRenderedText(font, to_string(playerInfo.at(i).at(2)), color);
        sprite = new Sprite(225 + i*250, 580, 104, 40);
        sprite->setTexture(texture);
        textures.insert(make_pair(to_string(i+3), texture));
        text.push_back(sprite);
    }
    TTF_CloseFont(font);
}
