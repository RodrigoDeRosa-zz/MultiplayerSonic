#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "../Graficos/Stage.hpp"
#include "../Graficos/Camara.hpp"
#include "Jugadores.hpp"
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
    vector <Stage*> stages;
    Stage* stageActual;
    int stageActualIndex; //Se agrega esto para hacer mas rapido el avance de stages
    Camara* camara;
  public:
    Juego();

    void setJugadores(Jugadores*);

    void setStage(Stage* stage); //Viejo
    /*Los stages se deben agregar en orden, porque despues en el transcurso del
    juego se iteran en orden*/
    void addStage(Stage* stage); //Nuevo

    /*Carga como stage actual al proximo stage de la lista*/
    void nextStage();

    bool addJugador(string nombreJugador, string ombrePersonaje);
    //por ahora renderiza al recibiendo una camara, luego lo hace con la camara de cada jugador
    void render();
    void setFactory();
    void setCamara(Camara* cam);

    //void updateJugadores(map <string, vector <float> >);
    void updateJugador(string, float, float, move_type, int, bool);
    void updateCamara(int, int);
    /*Actualiza un sprite del spriteGroup indicado en el stage actual*/
    void updateStage(string groupKey, int index, float x, float y);

    ~Juego();
};

#endif /*JUEGO_HPP*/
