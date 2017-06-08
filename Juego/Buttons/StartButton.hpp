#ifndef STARTBUTTON_HPP
#define STARTBUTTON_HPP

#include "../Button.hpp"

class StartButton : public Button{
    protected:
        void handleOnClick();
    public:
        StartButton(int x, int y);
        void render();
};

#endif /*STARTBUTTON_HPP*/
