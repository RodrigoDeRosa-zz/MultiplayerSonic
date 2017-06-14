#ifndef PLAYERSCORE_HPP
#define PLAYERSCORE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../Graficos/Texture.hpp"
#include "../../Graficos/Sprite.hpp"
#include "Score.hpp"
#include <string>
#include <map>
using namespace std;

class PlayerScore : public Score{
    private:
        map<string, Sprite*> sprites;
        bool online;
        int coins, hearts, points, position;
        TTF_Font* font;
        void updateText(string);
        void connect();
        void disconnect();
    public:
        PlayerScore(Texture*, TTF_Font* font, int offset);
        ~PlayerScore();
        /*Score methods*/
        void setScore(int);
        /*Life methods*/
        void setLives(int);
        /*Coins methods*/
        void setRings(int);
        /*Connection methods*/
        void toggleOnline(bool);
        /*Rendering*/
        void render();
        void kill();
};

#endif /*PLAYERSCORE_HPP*/
