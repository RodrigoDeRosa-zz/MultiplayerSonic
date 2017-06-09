#ifndef TRANSITIONSTAGETEAMS_HPP
#define TRANSITIONSTAGETEAMS_HPP

#include "TransitionStage.hpp"
#include <vector>
using namespace std;

class TransitionStageTeams : public TransitionStage{
    private:
        vector<vector<int>> teamInfo; //Se guarda rings, points, total de cada team
    public:
        TransitionStageTeams(int w, int h);
        void setTeamInfo(int team, int rings, int score, int total);
        void setValues();
};

#endif /*TRANSITIONSTAGETEAMS_HPP*/
