#include "ScoreController.hpp"
#include <string>
using namespace std;

#define PLAYERS 4

ScoreController::ScoreController(){
    /*Paths de texturas*/
    vector<string> paths;
    paths.push_back("Graficos/score1.png");
    paths.push_back("Graficos/score2.png");
    paths.push_back("Graficos/score3.png");
    paths.push_back("Graficos/score4.png");
    /*Se llena el vector de scores*/
    PlayerScore* player;
    Texture* tex;
    font = TTF_OpenFont("Graficos/font.ttf", 25); //Se inicializa la fuente
    int offset = 300; //Desplazamiento lateral de cada uno
    for (int i = 0; i < PLAYERS; i++){
        /*Creacion de textura*/
        tex = new Texture();
        tex->loadFromFile(paths.at(i));
        /*Creacion de score*/
        player = new PlayerScore(tex, font, offset*i);
        scores.push_back(player);
    }
}
ScoreController::~ScoreController(){
    for (int i = 0; i < scores.size(); i++){
        delete scores.at(i);
    }
    TTF_CloseFont(font);
}

void ScoreController::update(int index, int rings, int lives, int score, bool state){
    PlayerScore* player = scores.at(index);
    player->toggleOnline(state);
    player->setRings(rings);
    player->setLives(lives);
    player->setScore(score);
}

void ScoreController::render(){
    for (int i = 0; i < scores.size(); i++){
        scores.at(i)->render();
    }
}
