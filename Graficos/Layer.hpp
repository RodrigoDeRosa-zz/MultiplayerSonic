#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Camara.hpp"
using namespace std;

class Layer{
    private:
        Texture* texture;
        Sprite* image;
        unsigned char zIndex;
        string texPath;
        int width, height;
    public:
        Layer();//Constructor
        ~Layer();//Destructor
        void setIndexZ(unsigned char);
        void setTexPath(string);
        void setDimensions(int w, int h);
        /*Carga la imagen desde la direccion que se almaceno*/
        bool loadImage();
        void setTexture(Texture*);
        /*Presenta la imagen en pantalla*/
        void render(Camara*);
        void render();
        Texture* getTexture();

        bool operator<=(Layer&) const;
        /*Utilizado para comparar zIndex*/
        bool isBigger(unsigned char);

};

#endif /*LAYER_HPP*/
