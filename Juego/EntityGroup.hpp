#ifndef ENTITYGROUP_HPP
#define ENTITYGROUP_HPP

#include "Entity.hpp"
#include "../Graficos/Camara.hpp"
#include "../message.hpp"
#include <map>
#include <string>
#include <iostream>
using namespace std;

class EntityGroup{
    map<int, Entity*> entities; //Vector de punteros a Sprite
    int size;
    public:
        EntityGroup();
        ~EntityGroup();
        /*Agrega un sprite a la lista de sprites.*/
        void add(Entity*, int);
        /*Saca el sprite pedido de la lista*/
        void remove(int index);
        /*Renderiza todos los sprites del grupo*/
        void render(Camara*);
        /*Actualiza la entidad*/
        void update(int ,float, float, int);
        /*El ultimo es el sentido*/
        void update(int, float, float, int, move_type);
};


#endif /*ENTITYGROUP_HPP*/
