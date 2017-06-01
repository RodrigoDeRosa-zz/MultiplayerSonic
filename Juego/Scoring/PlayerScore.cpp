#include "PlayerScore.hpp"
#include <SDL2/SDL_image.h>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

PlayerScore::PlayerScore(string snP, string cP, string hP, string scP, string fP, int offset){
    online = false;
    coins = 0; hearts = 0; points = 0;
    position = offset;
    font = TTF_OpenFont(fP.c_str(), 25);

    Uint8 keyColor[3] = {0x0, 0xFF, 0xFF};
    //Textures
    textures.insert(make_pair("sonic", new Texture()));
    textures.at("sonic")->loadFromFile(snP, keyColor);
    textures.insert(make_pair("coin", new Texture()));
    textures.at("coin")->loadFromFile(cP, keyColor);
    textures.insert(make_pair("heart", new Texture()));
    textures.at("heart")->loadFromFile(hP, keyColor);
    textures.insert(make_pair("score", new Texture()));
    textures.at("score")->loadFromFile(scP, keyColor);
    //Text
    SDL_Color color = {0x0, 0x0, 0x0};
    textures.insert(make_pair("coinText", new Texture()));
    textures.at("coinText")->loadFromRenderedText(font, to_string(coins), color);
    textures.insert(make_pair("heartText", new Texture()));
    textures.at("heartText")->loadFromRenderedText(font, to_string(hearts), color);
    textures.insert(make_pair("scoreText", new Texture()));
    textures.at("scoreText")->loadFromRenderedText(font, to_string(points), color);
}

PlayerScore::~PlayerScore(){
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        delete it->second;
    }
}

void PlayerScore::updateText(string mode){
    SDL_Color color = {0x0, 0x0, 0x0};
    if (mode.compare(string("all"))){
        textures.at("coinText")->loadFromRenderedText(font, to_string(coins), color);
        textures.at("heartText")->loadFromRenderedText(font, to_string(hearts), color);
        textures.at("scoreText")->loadFromRenderedText(font, to_string(points), color);
    } else {
        if (mode.compare(string("coins")))
            textures.at("coinText")->loadFromRenderedText(font, to_string(coins), color);
        if (mode.compare(string("hearts")))
            textures.at("heartText")->loadFromRenderedText(font, to_string(hearts), color);
        if (mode.compare(string("points")))
            textures.at("scoreText")->loadFromRenderedText(font, to_string(points), color);
    }
}

void PlayerScore::setScore(int score){
    points = score;
    updateText(string("points"));
}

void PlayerScore::addScore(int score){
    points += score;
    updateText(string("points"));
}

/*Life methods*/
void PlayerScore::setLives(int lives){
    hearts = lives;
    updateText(string("hearts"));
}

//Resta una vida
void PlayerScore::subLife(){
    hearts -= 1;
    updateText(string("hearts"));
}

/*Coins methods*/
void PlayerScore::setRings(int rings){
    coins = rings;
    updateText(string("coins"));
}

void PlayerScore::addRings(int rings){
    coins += rings;
    updateText(string("coins"));
}

//Resta todas las monedas
void PlayerScore::clearRings(){
    coins = 0;
    updateText(string("coins"));
}

/*Connection methods*/
void PlayerScore::connect(){
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        it->second->setColorMod(0xFF, 0xFF, 0xFF);
    }
}
void PlayerScore::disconnect(){
    for (map<string, Texture*>::iterator it = textures.begin(); it != textures.end(); it++){
        it->second->setColorMod(0x80, 0x80, 0x80);
    }
}
/*Rendering*/
void PlayerScore::render(){
    textures.at("sonic")->render(position + 5, 5);
    textures.at("coin")->render(position + 5 + 50, 15);
    textures.at("coinText")->render(position + 5 + 80, 10);
    textures.at("heart")->render(position + 5 + 125, 15);
    textures.at("heartText")->render(position + 5 + 155, 10);
    textures.at("score")->render(position + 5 + 170, 15);
    textures.at("scoreText")->render(position + 5 + 200, 10);
}
