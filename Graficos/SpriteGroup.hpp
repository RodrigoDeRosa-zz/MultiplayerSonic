#ifndef SPRITEGROUP_HPP
#define SPRITEGROUP_HPP

#include "Sprite.hpp"
#include "Camara.hpp"
#include <map>
#include <string>
#include <iostream>
using namespace std;

class SpriteGroup{
    map<int, Sprite*> sprites; //Vector de punteros a Sprite
    int size;
    public:
        SpriteGroup();
        ~SpriteGroup();
        /*Agrega un sprite a la lista de sprites.*/
        void add(Sprite*);
        void add(Sprite*, int);
        /*Saca el sprite pedido de la lista*/
        void remove(Sprite);
        void remove(int index);
        /*Renderiza todos los sprites del grupo*/
        void render(Camara*);
        /*Remueve todos los sprites del grupo*/
        void empty();
        /*Verrifica si el sprite indicado es parte del grupo*/
        bool has(Sprite);
        map<int, Sprite*> getSprites();

        /*Este metodo es llamado desde el juego para actualizar
         * los sprites de el stage. recibe un int que es la posicion
         * en la lista, y los floats son las nuevas posiciones del
         * sprite.*/
        void update(int ,float, float);
};


#endif /*SPRITEGROUP_HPP*/
