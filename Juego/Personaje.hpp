#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include "../Juego/MovingBloque.hpp"
#include "../Graficos/Camara.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personaje{
  protected:
    MovingBloque* bloque_pers;
    string nombreJugador;
    int frameRight, frameLeft;
    void moveRight(float);
    void moveLeft(float);
    //void moveUp(float);

  public:
    //recibe un string de nombre de jugador que no puede estar repetido
    Personaje(string);
    //devuelve el nombre del jugador
    string getNombreJugador();
    //Renderiza el bloque interno, devuelve false si falla
    bool render(Camara*);
    void setMovingBloque(MovingBloque*);
    void update(float, float);
    bool operator==(Personaje& other) const;
    ~Personaje();
    int getX();
    int getY();

    // int getVelX();
    // int getVelY();

};

#endif /*PERSONAJE_HPP*/
