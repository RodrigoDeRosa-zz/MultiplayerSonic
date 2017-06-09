#ifndef SCORE_HPP
#define SCORE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../Graficos/Texture.hpp"
#include "../../Graficos/Sprite.hpp"
#include <string>
#include <map>
using namespace std;

class Score{
    public:
        Score();
        ~Score();
        /*Score methods*/
        virtual void setScore(int);
        /*Life methods*/
        virtual void setLives(int);
        /*Coins methods*/
        virtual void setRings(int);
        /*Connection methods*/
        virtual void toggleOnline(bool);
        /*Rendering*/
        virtual void render();
};

#endif /*SCORE_HPP*/
