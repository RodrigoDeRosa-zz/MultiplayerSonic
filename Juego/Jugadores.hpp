#ifndef JUGADORES_HPP
#define JUGADORES_HPP
using namespace std;

#include "Jugador.hpp"
#include "../Graficos/Camara.hpp"
#include "SegaFactory.hpp"
#include <string>
#include <iostream>
#include <map>

class Jugadores{
  private:
    map <string, Jugador*> jugadores;
    Jugador* jugadorActual;
    SegaFactory* factory;

    bool addSonic(string nombreJugador, string nombrePersonaje, Jugador* jug);

  public:
    Jugadores();
    /*Agrega un jugador a la lista de jugadores.*/
    bool addJugador(string nombreJugador, string nombrePersonaje);
    /*Saca el jugador pedido de la lista, devuelve valor booleano dependiendo de como ejecuto la operacion*/
    bool remove(string);
    void update();
    void setFactory(SegaFactory*);
    void render(Camara* camara);
    /*Remueve todos los jugadores*/
    void empty();
    /*Verrifica si el jugador indicado es parte del grupo*/
    bool has(string);

    ~Jugadores();
};


#endif /*JUGADORES_HPP*/
