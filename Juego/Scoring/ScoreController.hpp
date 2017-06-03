#ifndef SCORE_CONTROL_HPP
#define SCORE_CONTROL_HPP

#include "PlayerScore.hpp"
#include <SDL2/SDL_ttf.h>
#include <vector>
using namespace std;

class ScoreController{
    private:
        vector<PlayerScore*> scores;
        TTF_Font* font;
    public:
        ScoreController();
        ~ScoreController();
        /*Actualiza el estado de un jugador*/
        void update(int player, int rings, int lives, int score, bool state);
        /*Rendering*/
        void render(); //Renderiza a todos

};

#endif /*SCORE_CONTROL_HPP*/
