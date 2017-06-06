#ifndef INITSTAGE_HPP
#define INITSTAGE_HPP

#include "../Buttons/StartButton.hpp"
#include "SonicLogo.hpp"
#include "../../Graficos/Stage.hpp"
#include "../../Graficos/Texture.hpp"
#include <string>
using namespace std;

class InitStage : public Stage{
    private:
        map<string, Texture*> textures;
        StartButton* button;
        SonicLogo* logo;
    public:
        InitStage(int w, int h);
        ~InitStage();
        void render();
};

#endif /*INITSTAGE_HPP*/
