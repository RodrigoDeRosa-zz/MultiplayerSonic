#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include "../Juego/MovingBloque.hpp"
#include "../Graficos/Camara.hpp"
#include "ClipGroup.hpp"
#include "../message.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personaje{
  protected:
    MovingBloque* bloque_pers;
    string nombreJugador;
    MovingBloque* desaparecer;

  public:
    //recibe un string de nombre de jugador que no puede estar repetido
    Personaje(string);
    ~Personaje();
    //devuelve el nombre del jugador
    string getNombreJugador();
    void grisearBolque();
    void desGrisearBolque();
    void borrar();
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
