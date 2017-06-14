#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include "../Graficos/Camara.hpp"
#include "../Graficos/Texture.hpp"
#include "Entidades/Escudo.hpp"
#include "Entidades/Invencibilidad.hpp"
#include "Personaje.hpp"
#include "Sonic.hpp"
#include <iostream>
#include <string>

class Jugador{
    Personaje* personaje;
    state_type efectoActual;
    Escudo* escudo;
    Invencibilidad* invencibilidad;
    string nombreJugador;
    string nombrePersonaje;
    public:
    //recibe un string valido asociado al nombre del algun personaje
    //y un string de nombre de jugador que no puede estar repetido
    Jugador(string nomJugador, string nomPersonaje, Texture* bolas);
    //devuelve el nombre del jugador
    string getNombre();
    void setPersonaje(Personaje*);
    void setCamara(Camara*);
    void render(Camara*);
    void borrarPersonaje();
    bool operator==(Jugador& other) const;
    void updatePersonaje(float,float,move_type,int,bool, state_type, int);
    ~Jugador();
};

#endif /*JUGADOR_HPP*/
