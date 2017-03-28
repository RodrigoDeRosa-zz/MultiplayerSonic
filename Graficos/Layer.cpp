#include "Layer.hpp"
#include "Texture.hpp"
#include "Sprite.hpp"
#include "Window.hpp"
#include <string>
using namespace std;

Layer::Layer(){
    texture = NULL;
    image = NULL;
    zIndex = 0;
    texPath = "";
}

Layer::~Layer(){
    if (texture){
        delete texture;
        texture = NULL;
    }
    if(image){
        delete image;
        image = NULL;
    }
    zIndex = 0;
    texPath = "";
}

void Layer::setIndexZ(unsigned char z){
    zIndex = z;
}

void Layer::setTexPath(string path){
    texPath = path;
}

/*Carga la imagen desde la direccion que se almaceno*/
bool Layer::loadImage(){
    if(texPath == ""){
        printf("WARNING: No path to load texture from!\n");
    }else{
        /*Se crea la textura que ira de fondo*/
        texture = new Texture();
        if(!texture->loadFromFile(texPath)){
            printf("WARNING: Couldn't load layer texture!\n");
            delete texture;
            texture = NULL;
        };
    }
    /*Se crea el sprite que sera renderizado*/
    int width = Window::getInstance().getWidth();
    int height = Window::getInstance().getHeight();
    image = new Sprite(0, 0, width, height);
    image->setTexture(texture);
    return true;
}

/*Presenta la imagen en pantalla*/
void Layer::render(camara* camara){
    if(image) image->render(0,0,camara);
}
bool Layer::operator<=(Layer& other) const{
    return other.isBigger(zIndex);
}
bool Layer::isBigger(unsigned char z){
    return zIndex >= z;
}
