#include "Piedra.hpp"

using namespace std;

Piedra::Piedra(float x, float y) 
: Entidad(x,y){
	Efecto* efecto = new Efecto("posicion",0); // o como sea que definan el efecto para la piedra(de la forma que yo lo habia pensado esto era trivial)
	this->setEfecto(efecto);
}