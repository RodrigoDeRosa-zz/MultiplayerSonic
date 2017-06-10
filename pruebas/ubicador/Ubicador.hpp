#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Model.hpp"
//#include "Logger.hpp"//ojo si no hace falta ../ n cantidad de veces
//includes

using namespace std;

enum tipo_ent{COIN=0,CRAB,FLY,FISH,SPIKE,ROCK,BONUS,TIPO_ENT_TOTAL};

struct terna{
		tipo_ent tipo;
		int 	id;
		float	x;
		float	y;
};

typedef struct terna terna_t;//usar este nombre y fue

class Ubicador{
		vector<terna_t*>* ternas;
		vector<int>* mins;
		vector<int>* maxs;
	
	public:
		Ubicador();

		void setParams(int coin_min, int coin_max,
				int crab_min, int crab_max,
				int fly_min, int fly_max,
				int fish_min, int fish_max,
				int spike_min, int spike_max,
				int rock_min, int rock_max,
				int bonus_min, int bonus_max);
		
		vector<terna_t*>* generarTernas(int LvLen);
};
