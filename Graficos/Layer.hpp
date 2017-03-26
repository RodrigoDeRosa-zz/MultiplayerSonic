#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>
#include "Texture.hpp"
#include "Sprite.hpp"
using namespace std;

class Layer{
    private:
        Texture* texture;
        Sprite* image;
        unsigned char zIndex;
        string texPath;
    public:
        Layer();//Constructor
        ~Layer();//Destructor
        void setIndexZ(unsigned char);
        void setTexPath(string);
        /*Carga la imagen desde la direccion que se almaceno*/
        bool loadImage();
        /*Presenta la imagen en pantalla*/
        void render();
        bool operator<=(Layer&) const;
        /*Utilizado para comparar zIndex*/
        bool isBigger(unsigned char);
};

#endif /*LAYER_HPP*/