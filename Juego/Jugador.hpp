#ifndef JUEGADOR_HPP
#define JUEGADOR_HPP

#include "../Graficos/Camara.hpp"
#include <iostream>
#include <string>

class Jugador{
    camara* cam;
    string nombreJugador;
    string nombrePersonaje;
    public:
    //recibe un string valido asociado al nombre del algun personaje
    //y un string de nombre de jugador que no puede estar repetido
    Jugador(string nomJugador, string nomPersonaje);
    //devuelve el nombre del jugador
    string getNombre();
    void setCamara(camara*);
    bool operator==(Jugador& other) const;
    ~Jugador();
};

#endif /*JUEGADOR_HPP*/
