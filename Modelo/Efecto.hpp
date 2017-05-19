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