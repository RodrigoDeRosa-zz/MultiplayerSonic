#ifndef STARTBUTTON_HPP
#define STARTBUTTON_HPP

#include "../Button.hpp"
#include "../../message.hpp"
#define W 436
#define H 208

class StartButton : public Button{
    protected:
        virtual key_event handleOnClick();
    public:
        StartButton(int x, int y, int w = W, int h = H);
        void render();
};

#endif /*STARTBUTTON_HPP*/
