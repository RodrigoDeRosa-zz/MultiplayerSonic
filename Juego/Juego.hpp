#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "../Graficos/Stage.hpp"
#include "../Graficos/Camara.hpp"
#include "Jugadores.hpp"
#include <iostream>

/*El Juego tiene como atributos al Stage y a los Jugadores y es el responsable de relacionarlos para calcular
  colisiones entre ellos, entre otras cosas.
  Es resposabilidad del cliente verificar que al juego le lleguen tanto un stage como jugadores validos
  creados desde afuera (en este caso el jsonLoader)*/
class Juego{
    Jugadores* jugadores;
    Stage* stage;
  public:
    Juego();
    void setStage(Stage* stage);
    //por ahora renderiza al recibiendo una camara, luego lo hace con la camara de cada jugador
    void render(Camara* camara);
    ~Juego();
};

#endif /*JUEGO_HPP*/
