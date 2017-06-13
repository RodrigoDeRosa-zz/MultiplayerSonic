#ifndef CONNECTIONLOSTSTAGE_HPP
#define CONNECTIONLOSTSTAGE_HPP

#include "../../Graficos/Stage.hpp"

class ConnectionLostStage : public Stage{
    public:
        ConnectionLostStage(int w, int h);
        ~ConnectionLostStage();
        void render();
};

#endif /*CONNECTIONLOSTSTAGE_HPP*/
