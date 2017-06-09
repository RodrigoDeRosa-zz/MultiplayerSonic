#ifndef TRANSITIONSTAGECOOP_HPP
#define TRANSITIONSTAGECOOP_HPP

#include "TransitionStage.hpp"
#include <vector>
using namespace std;

class TransitionStageCoop : public TransitionStage{
    private:
        vector<int> coopInfo; //Se guarda rings, points, total
    public:
        TransitionStageCoop(int w, int h);
        void setCoopInfo(int rings, int score, int total);
        void setValues();
};

#endif /*TRANSITIONSTAGECOOP_HPP*/
