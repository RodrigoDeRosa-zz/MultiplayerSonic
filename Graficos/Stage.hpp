#ifndef STAGE_HPP
#define STAGE_HPP

#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "Camara.hpp"
#include <vector>

class Stage{
    private:

        SpriteGroup* sprites;
        //El sprites de arriba tiene que cambiarse por map <string, SpriteGroup*> spriteGroups;

        Layer* front;
        Layer* background;
        int width, height;
    public:
        Stage();
        ~Stage();
        /*Renderiza todos los elementos del escenario*/
        void render(Camara*);
        //Al render debe renderizar todos los SpriteGroups contenidos en el map.

        /*Agrega una capa y la define como front o background segun su z-index*/
        void addLayer(Layer*);

        /*Define el sprite group del escenario como el recibido*/
        void setSpriteGroup(SpriteGroup*);
        //el metodo anterior tiene que cambiarse por:
        //void setSpriteGroup(string, SpriteGroup*);
        //que agrega al map "spriteGroups" un nuevo SpriteGroup con el nombre pasado

        /*Agrega el sprite al sprite group*/
        void addSprite(Sprite*);
        //el metodo anterior tiene que cambiarse por:
        //void addSprite(string, Sprite*);
        //que agrega un nuevo sprite al group guardado en el mapa con ese nombre

        //COMENTARIO:
        //falta agregar un metodo:
        //void updateSprite(string, indiceSprite, new_pos_x, new_pos_y);
        //Debe acceder al SpriteGroup correspondiente representado por el string
        //y al tenerlo debe llamar al metodo update de la siguiente manera
        //spriteGroupPedido.update(indiceSprite, new_pos_x, new_pos_y);
        //este metodo ya esta implementado

        int getHeight();
        int getWidth();
		void setDimensions(int w, int h);
		Stage& getInstance();

};

#endif /*STAGE_HPP*/
