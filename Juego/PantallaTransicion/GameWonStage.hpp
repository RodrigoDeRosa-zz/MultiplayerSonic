#ifndef GAMEWONSTAGE_HPP
#define GAMEWONSTAGE_HPP

#include "../../Graficos/Stage.hpp"

class GameWonStage : public Stage{
    public:
        GameWonStage(int w, int h);
        ~GameWonStage();
        void render();
};

#endif /*GAMEWONSTAGE_HPP*/
