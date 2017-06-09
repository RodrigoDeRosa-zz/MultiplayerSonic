#ifndef SCORE_CONTROL_HPP
#define SCORE_CONTROL_HPP

#include "Score.hpp"
#include <SDL2/SDL_ttf.h>
#include <vector>
using namespace std;

class ScoreController{
    private:
        vector<Score*> scores;
        TTF_Font* font;
    public:
        ScoreController(int mode);
        ~ScoreController();
        /*Actualiza el estado de un jugador*/
        void update(int player, int rings, int lives, int score, bool state);
        void updateCoop(int rings, int score);
        void updateTeam(int team, int rings, int score);
        /*Rendering*/
        void render(); //Renderiza a todos

};

#endif /*SCORE_CONTROL_HPP*/
