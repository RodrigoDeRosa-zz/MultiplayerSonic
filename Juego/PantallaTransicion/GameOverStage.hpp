#ifndef GAMEOVERSTAGE_HPP
#define GAMEOVERSTAGE_HPP

#include "../../Graficos/Stage.hpp"

class GameOverStage : public Stage{
    public:
        GameOverStage(int w, int h);
        ~GameOverStage();
        void render();
};

#endif /*GAMEOVERSTAGE_HPP*/
