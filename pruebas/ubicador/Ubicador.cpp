
#include <random>
#include "Ubicador.hpp"

#define COIN_WIDTH 50
#define COIN_HEIGHT 50

#define FISH_WIDTH 50
#define FISH_HEIGHT 100
#define FISH_MOV_SPAN 1500		//cuantas veces se mueve para un lado
#define FISH_MOV_SPEED 0.3		//cuanto se mueve por vez

#define CRAB_WIDTH 70
#define CRAB_HEIGHT 50
#define CRAB_MOV_SPAN 1000		//cuantas veces se mueve para un lado
#define CRAB_MOV_SPEED 0.2		//cuanto se mueve por vez

#define FLY_WIDTH 70
#define FLY_HEIGHT 50
#define FLY_MOV_SPAN 250		//cuantas veces se mueve para un lado
#define FLY_MOV_SPEED 0.4		//cuanto se mueve por vez

#define ROCK_WIDTH 103
#define ROCK_HEIGHT 200

#define SPIKE_WIDTH 200
#define SPIKE_HEIGHT 40


Ubicador::Ubicador(){
	mins=new vector<int>();
	maxs=new vector<int>();
}

//defines para asegurar minimos y maximos (puede que este más acotado)
#define MIN_COINS	50	//por ejemplo esto asegura que nunca se va a generar un nivel en el que haya menos de MIN_COINS monedas, no importa el parametro que se pase
#define MAX_COINS	100	//y este dice que si le pasas 120 como max_coins igual el maximo es 100

#define MIN_CRABS	0
#define MAX_CRABS	15

#define MIN_FISHES	0
#define MAX_FISHES	20

#define MIN_FLIES	0
#define MAX_FLIES 	10

#define MIN_SPIKES	0
#define MAX_SPIKES	5

#define MIN_ROCKS	0
#define MAX_ROCKS	10

#define MIN_BONUSES	0
#define MAX_BONUSES	6

//utilidad
int _min(int a, int b){
	return (a < b ? a : b);
}

int _max(int a, int b){
	return (a > b ? a : b);
}
//para cada parametro que se le pasa lo acomoda si esta ido de mambo (min>=0, max<=cierto valor), y lo pushea en el vector de minimos o maximos.
//Por como esta hecho el enum hay que respetar los órdenes porque mins.at(FISH) va a dar el minimo para fish sin hacer un dicc
void Ubicador::setParams(int coin_min, int coin_max, int crab_min, int crab_max, int fly_min, int fly_max, int fish_min, int fish_max, int spike_min, int spike_max, int rock_min, int rock_max, int bonus_min, int bonus_max){
	
	//si estan vacios no pasa 1
	mins->clear();
	maxs->clear();

	//coins
	mins->push_back(_max(coin_min,MIN_COINS));
	maxs->push_back(_min(coin_max,MAX_COINS));
	//crabs
	mins->push_back(_max(crab_min,MIN_CRABS));
	maxs->push_back(_min(crab_max,MAX_CRABS));
	//flies
	mins->push_back(_max(fly_min,MIN_FLIES));
	maxs->push_back(_min(fly_max,MAX_FLIES));
	//fishes
	mins->push_back(_max(fish_min,MIN_FISHES));
	maxs->push_back(_min(fish_max,MAX_FISHES));
	//spikes
	mins->push_back(_max(spike_min,MIN_SPIKES));
	maxs->push_back(_min(spike_max,MAX_SPIKES));
	//rocks
	mins->push_back(_max(rock_min,MIN_ROCKS));
	maxs->push_back(_min(rock_max,MAX_ROCKS));
	//bonuses
	mins->push_back(_max(bonus_min,MIN_BONUSES));
	maxs->push_back(_min(bonus_max,MAX_BONUSES));
}

//Resuelve con los parametros dados lo que tiene que hacer		
vector<terna_t*>* Ubicador::generarTernas(int LvLen){
	
}
