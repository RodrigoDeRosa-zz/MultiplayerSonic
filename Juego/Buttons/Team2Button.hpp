#ifndef TEAM2BUTTON_HPP
#define TEAM2BUTTON_HPP

#include "StartButton.hpp"
#include "../../message.hpp"

class Team2Button : public StartButton{
    protected:
        key_event handleOnClick();
    public:
        Team2Button(int x, int y);
};

#endif /*TEAM2BUTTON_HPP*/
