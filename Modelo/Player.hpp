#include <string>
#include "../Juego/Sonic.hpp"

using namespace std;

class Player{
	string name;
	float x;
	float y;
	float vel;
	int eventCounterX;
	int eventCounterY;
	int eventCounterJump;
	bool jumping;
	bool connected;
	Sonic* sonic;
	public:
		Player(string name, Sonic* sonic);
		string getName();
		float getX();
		float getY();
		void setX(float x);
		void setY(float y);
		void updateXY(float dirX, float dirY);
		bool isConnected();
		void setConnected(bool connected);

	/* ACA TENEMOS QUE DEFINIR UNA FUNCION QUE SEA:
	 * void afectarseCon( entidad );
	 * Lo que hace esta funcion es calcular la colision
	 * y si es necesario hacer que la entidad afecte
	 * al personaje*/

	/*ACA TENEMOS QUE DEFINIR OTRA FUNCION :
	 * void aplicarEfecto( efecto );
	 * Lo que hace esta funcion es modificar los
	 * atributos del personaje de acuerdo al tipo
	 * de efecto que recibe. Osea maneja el efecto,
	 * y determina que atributo debe modificar, pero no
	 * como debe modificarlo. Esto ultimo es responsabilidad
	 * del efecto, este sabe si tiene que sumar o restar.*/
};
