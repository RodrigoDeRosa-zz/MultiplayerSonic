#ifndef TEAMSCORE_HPP
#define TEAMSCORE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../Graficos/Texture.hpp"
#include "../../Graficos/Sprite.hpp"
#include "Score.hpp"
#include <string>
#include <map>
using namespace std;

class TeamScore : public Score{
    private:
        map<string, Sprite*> sprites;
        int coins, points, position;
        TTF_Font* font;
        void updateText(string);
    public:
        TeamScore(Texture*, TTF_Font* font, int team);
        ~TeamScore();
        /*Score methods*/
        void setScore(int);
        /*Coins methods*/
        void setRings(int);
        /*Rendering*/
        void render();
};

#endif /*TEAMSCORE_HPP*/
