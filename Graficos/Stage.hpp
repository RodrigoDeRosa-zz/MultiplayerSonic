#ifndef STAGE_HPP
#define STAGE_HPP

#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "../Juego/EntityGroup.hpp"
#include "../Juego/Entity.hpp"
#include "../message.hpp"
#include "Camara.hpp"
#include <vector>
#include <map>
#include <string>
using namespace std;

class Stage{
    private:
        map<string, SpriteGroup*> spriteGroups; //Nuevo
        map<string, EntityGroup*> entityGroups; //Nuevo

        Layer* front;
        Layer* background;
        int width, height;

        SpriteGroup* getSpriteGroup(string key);
        EntityGroup* getEntityGroup(string key);
    public:
        Stage();
        ~Stage();
        /*Renderiza todos los elementos del escenario*/
        void render(Camara*);

        /*Agrega una capa y la define como front o background segun su z-index*/
        void addLayer(Layer*);

        /*Agrega un grupo de sprites al stage.
         * @param: {string} key que representara el grupo en el mapa de sprites group.
        */
        void addSpriteGroup(string, SpriteGroup*); //Viejo
        /*No hace falta recibir el spriteGroup, se crea adentro. SE DEJA LA VIEJA POR LAS DUDAS*/
        void addSpriteGroup(string);
        void addEntityGroup(string);

        /*Agrega el sprite recibido al sprite group que corresponde a la clave
         *pasada en el string.
         */
        void addSprite(string, Sprite*, int); //Nuevo
        void addEntity(string, Entity*, int); //Nuevo

        /*Actualiza la posicion del sprite cuyo indice se recibe, en el sprite
         *group guardado como valor de la clave recibida en el string en el mapa
         *de spriteGroups.
        */
        void updateSprite(string groupKey, int index, float x, float y);
        void updateEntity(string groupKey, int index, float x, float y, int frame);
        void updateEntity(string groupKey, int index, float x, float y, int frame, move_type sense);

        void removeSprite(string groupKey, int index);
        void removeEntity(string groupKey, int index);

        int getHeight();
        int getWidth();
		void setDimensions(int w, int h);
		Stage& getInstance();

};

#endif /*STAGE_HPP*/
