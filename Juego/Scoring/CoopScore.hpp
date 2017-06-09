#ifndef COOPSCORE_HPP
#define COOPSCORE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../Graficos/Texture.hpp"
#include "../../Graficos/Sprite.hpp"
#include "Score.hpp"
#include <string>
#include <map>
using namespace std;

class CoopScore : public Score{
    private:
        map<string, Sprite*> sprites;
        int coins, points;
        TTF_Font* font;
        void updateText(string);
    public:
        CoopScore(Texture*, TTF_Font* font);
        ~CoopScore();
        /*Score methods*/
        void setScore(int);
        /*Coins methods*/
        void setRings(int);
        /*Rendering*/
        void render();
};

#endif /*COOPSCORE_HPP*/
