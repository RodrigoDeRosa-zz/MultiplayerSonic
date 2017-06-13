#ifndef STAGE_HPP
#define STAGE_HPP

#include "Layer.hpp"
#include "SpriteGroup.hpp"
#include "../Juego/EntityGroup.hpp"
#include "../Juego/Entity.hpp"
#include "../Juego/Scoring/ScoreController.hpp"
#include "../message.hpp"
#include "Camara.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Stage{
    protected:
        map<string, SpriteGroup*> spriteGroups; //Nuevo
        map<string, EntityGroup*> entityGroups; //Nuevo

        ScoreController* score;
        Layer* front;
        Layer* background;
        int width, height;

        SpriteGroup* getSpriteGroup(string key);
        EntityGroup* getEntityGroup(string key);
    public:
        Stage();
        ~Stage();
        /*Renderiza todos los elementos del escenario*/
        virtual void render(Camara*);
        virtual void render();
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

        void initScore(int mode);
        void updateScore(int index, int rings, int lives, int points, bool state);

        void removeSprite(string groupKey, int index);
        void removeEntity(string groupKey, int index);

        virtual key_event processEvent(SDL_Event);

        int getHeight();
        int getWidth();
		void setDimensions(int w, int h);
		Stage& getInstance();
        virtual void setPlayerInfo(int, int, int, int);
        virtual void setValues();
        virtual void setClicked();
        virtual void unclick();

};

#endif /*STAGE_HPP*/
