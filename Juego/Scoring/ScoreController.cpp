#include "ScoreController.hpp"
#include "PlayerScore.hpp"
#include "CoopScore.hpp"
#include "TeamScore.hpp"
#include <string>
using namespace std;

#define PLAYERS 4

ScoreController::ScoreController(int mode){
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
    CoopScore* coop;
    TeamScore* team;
    /*Agrega los puntajes de coop o teams segun corresponda*/
    switch (mode) {
        case 0: break;
        case 1: //Coop
            tex = new Texture();
            tex->loadFromFile("Graficos/coopScore.png");
            coop = new CoopScore(tex, font);
            scores.push_back(coop);
            break;
        case 2: //Teams
            //Team 1
            tex = new Texture();
            tex->loadFromFile("Graficos/team1Score.png");
            team = new TeamScore(tex, font, 1);
            scores.push_back(team);
            //Team 2
            tex = new Texture();
            tex->loadFromFile("Graficos/team2Score.png");
            team = new TeamScore(tex, font, 2);
            scores.push_back(team);
            break;
    }
}
ScoreController::~ScoreController(){
    for (int i = 0; i < scores.size(); i++){
        delete scores.at(i);
    }
    TTF_CloseFont(font);
}

void ScoreController::update(int index, int rings, int lives, int score, bool state){
    Score* player = scores.at(index);
    if (rings == -1 || lives == -1 || score == -1){
        player->kill();
        return;
    }
    player->toggleOnline(state);
    player->setRings(rings);
    player->setLives(lives);
    player->setScore(score);
}

void ScoreController::updateCoop(int rings, int score){
    Score* coop = scores.at(4);
    coop->setRings(rings);
    coop->setScore(score);
}

void ScoreController::updateTeam(int team, int rings, int score){
    Score* teamS = scores.at((size_t)team+4);
    teamS->setRings(rings);
    teamS->setScore(score);
}

void ScoreController::render(){
    for (int i = 0; i < scores.size(); i++){
        scores.at(i)->render();
    }
}
