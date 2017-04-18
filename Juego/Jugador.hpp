#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include "../Graficos/Camara.hpp"
#include <iostream>
#include <string>

class Jugador{
    string nombreJugador;
    string nombrePersonaje;
    public:
    //recibe un string valido asociado al nombre del algun personaje
    //y un string de nombre de jugador que no puede estar repetido
    Jugador(string nomJugador, string nomPersonaje);
    //devuelve el nombre del jugador
    string getNombre();
    void setCamara(Camara*);
    void render(Camara*);
    bool operator==(Jugador& other) const;
    ~Jugador();
};

#endif /*JUGADOR_HPP*/
