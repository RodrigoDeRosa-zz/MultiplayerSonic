#include "Efecto.hpp"

using namespace std;

Efecto::Efecto(string atributo, int cantidad){
	this->atributo = atributo;
	this->cantidad = cantidad;
}

string Efecto::getAtributo(){
	return this->atributo;
}

int Efecto::getCantidad(){
	return this->cantidad;
}