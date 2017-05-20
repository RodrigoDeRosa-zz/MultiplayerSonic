#ifndef EFECTO_HPP
#define EFECTO_HPP

#include <string>

using namespace std;

class Efecto{
	string atributo;
	int cantidad;
public:
	Efecto(string atributo, int cantidad);
	string getAtributo();
	int getCantidad();
};

#endif /*EFECTO_HPP*/