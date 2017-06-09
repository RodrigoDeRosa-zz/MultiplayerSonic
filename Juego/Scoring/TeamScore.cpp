#include "TeamScore.hpp"
#include <SDL2/SDL_image.h>
#include <sstream>
#include <string>
using namespace std;

TeamScore::TeamScore(Texture* tex, TTF_Font* ttf, int team) : Score(){
    coins = 0; points = 0;
    font = ttf;
    switch (team) {
        case 1:
            position = 330; break;
        case 2:
            position = 640; break;
    }

    Uint8 keyColor[3] = {0x0, 0xFF, 0xFF};
    //Graficos
    sprites.insert(make_pair("main", new Sprite(position, 60, 225, 40)));
    sprites.at("main")->setTexture(tex);
    //Texto
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    Texture* texture;
    /*Coins*/
    texture = new Texture();
    texture->loadFromRenderedText(font, to_string(coins), color);
    sprites.insert(make_pair("coinText", new Sprite(position + 80, 62, 45, 30)));
    sprites.at("coinText")->setTexture(texture);
    /*Points*/
    texture = new Texture();
    texture->loadFromRenderedText(font, to_string(points), color);
    sprites.insert(make_pair("scoreText", new Sprite(position + 155, 62, 100, 30)));
    sprites.at("scoreText")->setTexture(texture);
}

TeamScore::~TeamScore(){
    for (map<string, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
        delete it->second;
    }
}

void TeamScore::updateText(string mode){
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    Texture* tex = new Texture();
    /*Se agarra la textura, se la actualiza, y se la devuelve*/
    if (!mode.compare(string("coins"))){
        Sprite* coinsT = sprites.at("coinText");
        tex->loadFromRenderedText(font, to_string(coins), color);
        coinsT->setTexture(tex);
    } else if (!mode.compare(string("points"))){
        Sprite* pointsT = sprites.at("scoreText");
        tex->loadFromRenderedText(font, to_string(points), color);
        pointsT->setTexture(tex);
    }
}

void TeamScore::setScore(int score){
    if (score == points) return;
    points = score;
    updateText(string("points"));
}

/*Coins methods*/
void TeamScore::setRings(int rings){
    if (coins == rings) return;
    coins = rings;
    updateText(string("coins"));
}

/*Rendering*/
void TeamScore::render(){
    sprites.at("main")->render();
    sprites.at("coinText")->render();
    sprites.at("scoreText")->render();
}
