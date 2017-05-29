#include "EntityGroup.hpp"
#include <vector>
#include <algorithm>
using namespace std;

EntityGroup::EntityGroup(){}
EntityGroup::~EntityGroup(){
    for (map<int, Entity*>::iterator it = entities.begin(); it != entities.end(); it++){
        if (it->second){
            delete it->second;
        }
    }
}

void EntityGroup::add(Entity* entity, int index){
    entities.insert(make_pair(index, entity));
}

void EntityGroup::remove(int index){
    entities.erase(index);
}

void EntityGroup::update(int index, float new_x, float new_y, int frame){
    map<int, Entity*>::iterator it;
    it = entities.find(index);
    Entity* entity = it->second;
    entity->setFrame(frame);
    entity->update(new_x, new_y);
}

void EntityGroup::update(int index, float new_x, float new_y, int frame, move_type sense){
    map<int, Entity*>::iterator it;
    it = entities.find(index);
    Entity* entity = it->second;
    entity->setFrame(frame, sense);
    entity->update(new_x, new_y);
}


/*Funcion de ordenamiento del array de entities*/
struct order{
    inline bool operator() (Entity* sprite1, Entity* sprite2){
        return ( sprite1->getZIndex() < sprite2->getZIndex());
    }
};

void EntityGroup::render(Camara* camara){
    if (!entities.empty()) {
        vector<Entity*> v;
        for (map<int, Entity*>::iterator it = entities.begin(); it != entities.end(); it++){
            v.push_back(it->second);
        }
        std::sort(v.begin(), v.end(), order());
        for (int i = 0; i < (int)v.size(); i++) {
            v[i]->render(camara);
        }
    }
}
