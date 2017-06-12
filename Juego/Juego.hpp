#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "../Graficos/Stage.hpp"
#include "../Graficos/Camara.hpp"
#include "../message.hpp"
#include "Jugadores.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

/*El Juego tiene como atributos al Stage y a los Jugadores y es el responsable de relacionarlos para calcular
  colisiones entre ellos, entre otras cosas.
  Es resposabilidad del cliente verificar que al juego le lleguen tanto un stage como jugadores validos
  creados desde afuera (en este caso el jsonLoader)*/
class Juego{
    Jugadores* jugadores;
    map<string, Texture*> texturas;
    /*Se setean las texturas de todas las entidades*/
    void setTexturas();
    vector <Stage*> stages;
    Stage* stageActual;
    int stageActualIndex; //Se agrega esto para hacer mas rapido el avance de stages
    Camara* camara;
    Stage* createLevel(int, gameMode);
  public:
    Juego(gameMode);

    void setJugadores(Jugadores*);

    void setStage(Stage* stage); //Viejo
    /*Los stages se deben agregar en orden, porque despues en el transcurso del
    juego se iteran en orden*/
    void addStage(Stage* stage); //Nuevo

    /*Carga como stage actual al proximo stage de la lista*/
    void nextStage();

    bool addJugador(string nombreJugador, string nombrePersonaje);
    //por ahora renderiza al recibiendo una camara, luego lo hace con la camara de cada jugador
    void render();
    void renderNoCam();
    void setFactory();
    void setCamara(Camara* cam);
    void setStageScore(int mode);
    key_event processEvent(SDL_Event);
    bool stageReady();

    //void updateJugadores(map <string, vector <float> >);
    void updateJugador(string id, float posx, float posy, move_type movimiento, int frame, bool conectado,
        int rings, int lives, int points, state_type state, int state_frame);
    void updateCamara(int, int);
    /*Actualiza un sprite del spriteGroup indicado en el stage actual*/
    void updateStageSprite(string groupKey, out_message_t*);
    void updateStageEntity(string groupKey, out_message_t*);
    void updateStageEntitySense(string groupKey, out_message_t*);
    /*Agrega un sprite al spriteGroup indicado, en el stage actua*/
    void addSprite(string groupKey, Sprite* sprite, int);
    /*Agrega un spriteGroup en el stage actual*/
    void addSpriteGroup(string groupKey);
    void addEntityGroup(string groupKey);

    /*Actualizacion de entidades*/
    void updateMoneda(out_message_t*);
    void updateCangrejo(out_message_t*);
    void updateMosca(out_message_t*);
    void updatePez(out_message_t*);
    void updateBonus(out_message_t*);
    void updateBoss(out_message_t*);
    void updateBossBall(out_message_t*);

    /*Agrega una piedra en las posiciones dadas*/
    void addPiedra(float x, float y, int t, int index, int level);
    /*Agrega pinches en las posiciones dadas*/
    void addPinche(float x, float y, int index, int level);
    /*Agrega una moneda en las posiciones dadas*/
    void addMoneda(float x, float y, int index, int level);
    /*Agrega un bonus en las posiciones dadas*/
    void addBonus(float x, float y, int t, int index, int level);
    /*Agrega un pez en las posiciones dadas*/
    void addPez(float x, float y, int index, int level);
    /*Agrega un cangrejo en las posiciones dadas*/
    void addCangrejo(float x, float y, int index, int level);
    /*Agrega una mosca en las posiciones dadas*/
    void addMosca(float x, float y, int index, int level);
    /*Agrega un Jefe en las posiciones dadas*/
    void addBoss(float x, float y, int index);
    /*Agrega la bola del Jefe en las posiciones dadas*/
    void addBossBall(float x, float y, int index);

    ~Juego();
};

#endif /*JUEGO_HPP*/
