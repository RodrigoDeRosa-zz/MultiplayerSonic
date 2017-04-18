#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include "../Graficos/Bloque.hpp"
#include "../Graficos/Camara.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personaje{
    Bloque* bloque_pers;
    string nombreJugador;
  public:
    //recibe un string de nombre de jugador que no puede estar repetido
    Personaje(string);
    //devuelve el nombre del jugador
    string getNombreJugador();
    //Renderiza el bloque interno, devuelve false si falla
    bool render(Camara*);
    void setBloque(Bloque*);
    bool operator==(Personaje& other) const;
    ~Personaje();
};

#endif /*PERSONAJE_HPP*/
