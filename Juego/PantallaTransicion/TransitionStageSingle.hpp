#ifndef TRANSITIONSTAGESINGLE_HPP
#define TRANSITIONSTAGESINGLE_HPP

#include "TransitionStage.hpp"
using namespace std;

class TransitionStageSingle : public TransitionStage{
    public:
        TransitionStageSingle(int w, int h);
        void setValues();
};

#endif /*TRANSITIONSTAGESINGLE_HPP*/
