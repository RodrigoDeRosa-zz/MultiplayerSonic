#ifndef CONNECTBUTTON_HPP
#define CONNECTBUTTON_HPP

#include "../Button.hpp"
#include "../../message.hpp"
#define W 436
#define H 208

class ConnectButton : public Button{
    protected:
        virtual key_event handleOnClick();
    public:
        ConnectButton(int x, int y, int w = W, int h = H);
        void render();
};

#endif /*STARTBUTTON_HPP*/
