#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include "../Graficos/Camara.hpp"
#include "Personaje.hpp"
#include "Sonic.hpp"
#include <iostream>
#include <string>

class Jugador{
    Personaje* personaje;
    string nombreJugador;
    string nombrePersonaje;
    public:
    //recibe un string valido asociado al nombre del algun personaje
    //y un string de nombre de jugador que no puede estar repetido
    Jugador(string nomJugador, string nomPersonaje);
    //devuelve el nombre del jugador
    string getNombre();
    void setPersonaje(Personaje*);
    void setCamara(Camara*);
    void render(Camara*);
    bool operator==(Jugador& other) const;
    void updatePersonaje(float,float,float,float,float);
    ~Jugador();
};

#endif /*JUGADOR_HPP*/
