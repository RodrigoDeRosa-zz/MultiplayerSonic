#include "PlayerScore.hpp"
#include <SDL2/SDL_image.h>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

PlayerScore::PlayerScore(Texture* tex, TTF_Font* ttf, int offset){
    online = false;
    coins = 0; hearts = 0; points = 0;
    position = offset + 3;
    font = ttf;

    Uint8 keyColor[3] = {0x0, 0xFF, 0xFF};
    //Graficos
    sprites.insert(make_pair("main", new Sprite(position, 10, 295, 40)));
    sprites.at("main")->setTexture(tex);
    sprites.at("main")->setColorMod(0x80, 0x80, 0x80);
    //Texto
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    Texture* texture;
    /*Coins*/
    texture = new Texture();
    texture->loadFromRenderedText(font, to_string(coins), color);
    sprites.insert(make_pair("coinText", new Sprite(position + 80, 12, 45, 30)));
    sprites.at("coinText")->setTexture(texture);
    /*Hearts*/
    texture = new Texture();
    texture->loadFromRenderedText(font, to_string(hearts), color);
    sprites.insert(make_pair("heartText", new Sprite(position + 155, 12, 20, 30)));
    sprites.at("heartText")->setTexture(texture);
    /*Points*/
    texture = new Texture();
    texture->loadFromRenderedText(font, to_string(points), color);
    sprites.insert(make_pair("scoreText", new Sprite(position + 200, 12, 100, 30)));
    sprites.at("scoreText")->setTexture(texture);
}

PlayerScore::~PlayerScore(){
    for (map<string, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++){
        delete it->second;
    }
}

void PlayerScore::updateText(string mode){
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    Texture* tex = new Texture();
    /*Se agarra la textura, se la actualiza, y se la devuelve*/
    if (!mode.compare(string("coins"))){
        Sprite* coinsT = sprites.at("coinText");
        tex->loadFromRenderedText(font, to_string(coins), color);
        coinsT->setTexture(tex);
    } else if (!mode.compare(string("hearts"))){
        Sprite* heartsT = sprites.at("heartText");
        tex->loadFromRenderedText(font, to_string(hearts), color);
        heartsT->setTexture(tex);
    } else if (!mode.compare(string("points"))){
        Sprite* pointsT = sprites.at("scoreText");
        tex->loadFromRenderedText(font, to_string(points), color);
        pointsT->setTexture(tex);
    }
}

void PlayerScore::setScore(int score){
    if (score == points) return;
    points = score;
    updateText(string("points"));
}

/*Life methods*/
void PlayerScore::setLives(int lives){
    if (hearts == lives) return;
    hearts = lives;
    updateText(string("hearts"));
}

/*Coins methods*/
void PlayerScore::setRings(int rings){
    if (coins == rings) return;
    coins = rings;
    updateText(string("coins"));
}

void PlayerScore::toggleOnline(bool state){
    if ( (state && online) || (!state && !online)) return;
    if (state) connect();
    else disconnect();
    online = state;
}

/*Connection methods*/
void PlayerScore::connect(){
    sprites.at("main")->setColorMod(0xFF, 0xFF, 0xFF);
}
void PlayerScore::disconnect(){
    sprites.at("main")->setColorMod(0x80, 0x80, 0x80);
}

/*Rendering*/
void PlayerScore::render(){
    sprites.at("main")->render();
    sprites.at("coinText")->render();
    sprites.at("heartText")->render();
    sprites.at("scoreText")->render();
}
