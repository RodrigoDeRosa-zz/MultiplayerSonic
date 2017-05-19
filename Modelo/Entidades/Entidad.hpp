#include "../Efecto.hpp"

class Entidad{
protected:
	float x;
	float y;
	Efecto* efecto;
public:
	Entidad(float x, float y);
	float getX();
	float getY();
	Efecto* getEfecto();
	void setEfecto(Efecto* efecto);
};