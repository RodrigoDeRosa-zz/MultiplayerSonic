#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../../Texture.hpp"
#include <string>
#include <map>
using namespace std;

class PlayerScore{
    private:
        map<string, Texture*> textures;
        bool online;
        int coins, hearts, points, position;
        TTF_Font* font;
        void updateText(string);
    public:
        PlayerScore(string sonicPath, string coinPath, string heartPath, string scorePath,
            string fontPath, SDL_Renderer* renderer, int offset);
        ~PlayerScore();
        /*Score methods*/
        void setScore(int);
        void addScore(int);
        /*Life methods*/
        void setLives(int);
        void subLife(); //Resta una vida
        /*Coins methods*/
        void setRings(int);
        void addRings(int);
        void clearRings(); //Resta todas las monedas
        /*Connection methods*/
        void connect();
        void disconnect();
        /*Rendering*/
        void render();
};

#endif /*PLAYER_HPP*/
