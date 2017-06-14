#include "Plataforma.hpp"
#include "../Player.hpp"
#include <stdio.h>
#define WIDTH 345
#define HEIGHT 100
/*este factor es para chequear que el borde de abajo del jugador no sea una poco mas bajo que el borde de arriba de la piedra,
sino una distacia considerable, de modo que se pueda diferenciar una colision desde arriba de las de costado*/
#define FACTOR_DIFERENCIAL_H 5
#define THRESHOLD_DIST	45.0
#define THRESHOLD_MIN	15.0

using namespace std;


Plataforma::Plataforma(int id, float x, float y) : Entidad(id,x,y,WIDTH,HEIGHT){}

bool Plataforma::esPlataforma(){
    return true;
}

void Plataforma::afectarA(Player* jugador){

    if((jugador->getBordeAbajo()) < (this->Entidad::getBordeArriba() - FACTOR_DIFERENCIAL_H)){

        printf("entro \n");

        float posicion = this->Entidad::getBordeArriba() -  (jugador->getBordeAbajo() - jugador->getBordeArriba()); /*el alto del frame actual*/
        //float posicion = jugador-> getBordeArriba() - ( this->Entidad::getBordeAbajo() - this->Entidad::getBordeArriba());

        if (jugador->getX() > (this->Entidad::getBordeDer() - THRESHOLD_DIST) && jugador->estaMirandoADer()){
            jugador->caer(1);
            jugador->setBaseY(425);
            if (jugador->getX() > (this->Entidad::getBordeDer() - THRESHOLD_MIN)){
                //jugador->setY(posicion);
            }
            return;
        }
        if (jugador->getBordeDer() < (this->Entidad::getBordeIzq() + THRESHOLD_DIST) && !(jugador->estaMirandoADer())){
            jugador->caer(-1);
            jugador->setBaseY(425);
            if (jugador->getBordeDer() < (this->Entidad::getBordeIzq() + THRESHOLD_MIN)){
                //jugador->setY(posicion);
            }
            return;
        }

        //esta en el medio
        if (jugador->getY() > posicion){
            jugador->setY(posicion);
        }
        jugador->setBaseY(posicion);
    }
}

out_message_t* Plataforma::getOutMessage(){
	return this->Entidad::getOutMessage(MESSAGE_TOTAL);
}

out_message_t* Plataforma::getInitMessage(){
	return this->Entidad::getOutMessage(PLATFORM_SET);
}
