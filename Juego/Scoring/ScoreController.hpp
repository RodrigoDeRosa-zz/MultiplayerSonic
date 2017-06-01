#ifndef SCORE_CONTROL_HPP
#define SCORE_CONTROL_HPP

#include <vector>
using namespace std;

class ScoreController{
    private:
        vector<PlayerScore*> scores;
    public:
        ScoreController();
        ~ScoreController();
        void setScore(int player, int score);

};

#endif /*SCORE_CONTROL_HPP*/
