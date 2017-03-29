#ifndef STAGE_HPP
#define STAGE_HPP

#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "Camara.hpp"

class Stage{
    private:
        SpriteGroup* sprites;
        Layer* front;
        Layer* background;
        int width, height;
    public:
        Stage();
        ~Stage();
        /*Renderiza todos los elementos del escenario*/
        void render(camara*);

        /*Agrega una capa y la define como front o background segun su z-index*/
        void addLayer(Layer*);
        /*Define el sprite group del escenario como el recibido*/
        void setSpriteGroup(SpriteGroup*);
        /*Agrega el sprite al sprite group*/
        void addSprite(Sprite*);

        int getHeight();
        int getWidth();
		    void setDimensiones(int w, int h);


};

#endif /*STAGE_HPP*/
