#ifndef CONNECTSTAGE_HPP
#define CONNECTSTAGE_HPP

#include "SonicLogo.hpp"
#include "../../Graficos/Stage.hpp"
#include "../../Graficos/Texture.hpp"
#include "../Buttons/ConnectButton.hpp"
#include <SDL2/SDL.h>
#include "../../message.hpp"
#include <string>
using namespace std;

class ConnectionStage : public Stage{
    private:
        map<string, Texture*> textures;
        ConnectButton* button;
        SonicLogo* logo;
        bool clicked;
        unsigned int logoFrame;
    public:
        ConnectionStage(int w, int h);
        ~ConnectionStage();
        void render();
        key_event processEvent(SDL_Event);
        void setClicked();
        void unclick();
};

#endif /*CONNECTSTAGE_HPP*/
