#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include "../Juego/MovingBloque.hpp"
#include "../Graficos/Camara.hpp"
#include "ClipGroup.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personaje{
  protected:
    MovingBloque* bloque_pers;
    string nombreJugador;
    int frameRight, frameLeft;
    float direccionX, direccionY;
    void moveRight(float);
    void moveLeft(float);
    void jump(float,float);

  public:
    //recibe un string de nombre de jugador que no puede estar repetido
    Personaje(string);
    ~Personaje();
    //devuelve el nombre del jugador
    string getNombreJugador();
    void printMap();
    void grisearBolque();
    void desGrisearBolque();
    /*setters*/
    void setMovingBloque(MovingBloque*);
    void setClip(string);
    void setRectangulo(string, int, int ,int ,int);
    //Renderiza el bloque interno, devuelve false si falla
    bool render(Camara*);
    void update(float, float, float = -1.0, float = -1.0);
    bool operator==(Personaje& other) const;
    float getX();
    float getY();
    float getDirX();
    float getDirY();

};
#endif /*PERSONAJE_HPP*/
