#ifndef TEAM1BUTTON_HPP
#define TEAM1BUTTON_HPP

#include "StartButton.hpp"
#include "../../message.hpp"

class Team1Button : public StartButton{
    protected:
        key_event handleOnClick();
    public:
        Team1Button(int x, int y);
};

#endif /*TEAM1BUTTON_HPP*/
