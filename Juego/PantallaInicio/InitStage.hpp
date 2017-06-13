#ifndef INITSTAGE_HPP
#define INITSTAGE_HPP

#include "../Buttons/StartButton.hpp"
#include "SonicLogo.hpp"
#include "../../Graficos/Stage.hpp"
#include "../../Graficos/Camara.hpp"
#include "../../Graficos/Texture.hpp"
#include <SDL2/SDL.h>
#include "../../message.hpp"
#include <string>
#include <vector>
using namespace std;

class InitStage : public Stage{
    private:
        map<string, Texture*> textures;
        vector<StartButton*> buttons;
        vector<Texture*> waitTex;
        SonicLogo* logo;
        bool clicked;
        unsigned int logoFrame;
    public:
        InitStage(int w, int h, int type);
        ~InitStage();
        void render();
        void render(Camara*);
        void setClicked();
        key_event processEvent(SDL_Event);
};

#endif /*INITSTAGE_HPP*/
