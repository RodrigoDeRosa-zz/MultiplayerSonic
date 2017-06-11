#ifndef TRANSITIONSTAGE_HPP
#define TRANSITIONSTAGE_HPP

#include "SonicSmallLogo.hpp"
#include "../../Graficos/Stage.hpp"
#include "../../Graficos/Texture.hpp"
#include "../../Graficos/Sprite.hpp"
#include "../../Graficos/Camara.hpp"
#include <string>
#include <map>
#include <vector>
using namespace std;

class TransitionStage : public Stage{
    protected:
        map<string, Texture*> textures;
        vector<Sprite*> text;
        SonicSmallLogo* logo;
        /*Info que se renderiza en texto*/
        vector< vector<int> > playerInfo;
        unsigned int logoFrame;
    public:
        TransitionStage(int w, int h);
        ~TransitionStage();
        void setPlayerInfo(int player, int rings, int points, int total);
        virtual void setValues();
        void render();
        void render(Camara*);
};

#endif /*TRANSITIONSTAGE_HPP*/
