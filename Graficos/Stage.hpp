#ifndef STAGE_HPP
#define STAGE_HPP

#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "Camara.hpp"
#include <vector>
#include <map>
#include <string>
using namespace std;

class Stage{
    private:
        SpriteGroup* sprites; //Viejo
        map<string, SpriteGroup*> spriteGroups; //Nuevo

        Layer* front;
        Layer* background;
        int width, height;

        SpriteGroup* getSpriteGroup(string key);
    public:
        Stage();
        ~Stage();
        /*Renderiza todos los elementos del escenario*/
        void render(Camara*);
        //Al render debe renderizar todos los SpriteGroups contenidos en el map.

        /*Agrega una capa y la define como front o background segun su z-index*/
        void addLayer(Layer*);

        /*Define el sprite group del escenario como el recibido*/
        void setSpriteGroup(SpriteGroup*); //Viejo
        /*Agrega un grupo de sprites al stage.
         * @param: {string} key en el mapa de sprites group.
        */
        void addSpriteGroup(string, SpriteGroup*); //Nuevo

        /*Agrega el sprite al sprite group*/
        void addSprite(Sprite*); //Viejo
        /*Agrega el sprite recibido al sprite group que corresponde a la clave
         *pasada en el string.
         */
        void addSprite(string, Sprite*); //Nuevo

        /*Actualiza la posicion del sprite cuyo indice se recibe, en el sprite
         *group guardado como valor de la clave recibida en el string en el mapa
         *de spriteGroups.
        */
        void updateSprite(string groupKey, int index, float x, float y);

        int getHeight();
        int getWidth();
		void setDimensions(int w, int h);
		Stage& getInstance();

};

#endif /*STAGE_HPP*/
