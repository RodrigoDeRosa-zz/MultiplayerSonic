#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include "../Juego/MovingBloque.hpp"
#include "../Graficos/Camara.hpp"
#include "ClipGroup.hpp"
#include <iostream>
#include <string>
using namespace std;

enum move_type{IDLED, IDLEI, JUMPD, JUMPI, RUND, RUNI, WALKD, WALKI, MOVE_TOTAL};

class Personaje{
  protected:
    MovingBloque* bloque_pers;
    string nombreJugador;

  public:
    //recibe un string de nombre de jugador que no puede estar repetido
    Personaje(string);
    ~Personaje();
    //devuelve el nombre del jugador
    string getNombreJugador();
    void grisearBolque();
    void desGrisearBolque();
    /*setters*/
    void setMovingBloque(MovingBloque*);
    //Renderiza el bloque interno, devuelve false si falla
    bool render(Camara*);
    void update(float, float, move_type, int);
    bool operator==(Personaje& other) const;
    float getX();
    float getY();

};
#endif /*PERSONAJE_HPP*/
