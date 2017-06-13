#include "Ubicador.hpp"

#define Y_PIEDRA 345
#define Y_PINCHE 495
#define Y_CANGREJO	475
#define Y_PEZ	675
#define Y_BONUS	426
#define Y_MOSCA 225

#define COIN_WIDTH 50
#define COIN_HEIGHT 50
#define COIN_SPACE 10

#define FISH_WIDTH 50
#define FISH_HEIGHT 100
#define FISH_MOV_SPAN 1500		//cuantas veces se mueve para un lado
#define FISH_MOV_SPEED 0.3		//cuanto se mueve por vez
#define FISH_SPACE 30

#define CRAB_WIDTH 70
#define CRAB_HEIGHT 50
#define CRAB_MOV_SPAN 1000		//cuantas veces se mueve para un lado
#define CRAB_MOV_SPEED 0.2		//cuanto se mueve por vez
#define CRAB_SPACE	310

#define FLY_WIDTH 70
#define FLY_HEIGHT 50
#define FLY_MOV_SPAN 250		//cuantas veces se mueve para un lado
#define FLY_MOV_SPEED 0.4		//cuanto se mueve por vez
#define FLY_SPACE 150	

#define ROCK_WIDTH 103
#define ROCK_HEIGHT 200
#define ROCK_SPACE 250

#define SPIKE_WIDTH 200
#define SPIKE_HEIGHT 40
#define SPIKE_SPACE 200

#define BONUS_WIDTH 100
#define BONUS_SPACE 50
using namespace std;

Ubicador::Ubicador(){
	mins=new vector<int>();
	maxs=new vector<int>();
	srand(time(NULL));
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
void fixPar(int* mn, int* mx, int absmin, int absmax){
	*mn = (*mn > absmax ? absmin+1 : *mn);
	*mx = (*mx < absmin ? absmax-1 : *mx);
	if (*mn > *mx){
		int aux = *mn;
		*mn=*mx;
		*mx=aux;
	}
}

int _min(int a, int b){
	return (a < b ? a : b);
}

int _max(int a, int b){
	return (a > b ? a : b);
}

bool estaLibre(vector<float>* izq, vector<float>* der, float newi, float newd){
	for (int i = 0; i < izq->size(); i++){
		if (!(izq->at(i) > newd || der->at(i) < newi)){
			return false;
		}
	}
	return true;
}


#define MAX_ITERS 1000
#define ESPACIO_FINAL 500
//para cada parametro que se le pasa lo acomoda si esta ido de mambo (min>=0, max<=cierto valor), y lo pushea en el vector de minimos o maximos.
//Por como esta hecho el enum hay que respetar los órdenes porque mins.at(FISH) va a dar el minimo para fish sin hacer un dicc
void Ubicador::setParams(int coin_min, int coin_max, int crab_min, int crab_max, int fly_min, int fly_max, int fish_min, int fish_max, int spike_min, int spike_max, int rock_min, int rock_max, int bonus_min, int bonus_max){
	
	//si estan vacios no pasa 1
	mins->clear();
	maxs->clear();

	//coins (0)
	fixPar(&coin_min,&coin_max,MIN_COINS,MAX_COINS);
	mins->push_back(_max(coin_min,MIN_COINS));
	maxs->push_back(_min(coin_max,MAX_COINS));
	//crabs (1)
	fixPar(&crab_min,&crab_max,MIN_CRABS,MAX_CRABS);
	mins->push_back(_max(crab_min,MIN_CRABS));
	maxs->push_back(_min(crab_max,MAX_CRABS));
	//flies (2)
	fixPar(&fly_min,&fly_max,MIN_FLIES,MAX_FLIES);
	mins->push_back(_max(fly_min,MIN_FLIES));
	maxs->push_back(_min(fly_max,MAX_FLIES));
	//fishes (3)
	fixPar(&fish_min,&fish_max,MIN_FISHES,MAX_FISHES);
	mins->push_back(_max(fish_min,MIN_FISHES));
	maxs->push_back(_min(fish_max,MAX_FISHES));
	//spikes (4)
	fixPar(&spike_min,&spike_max,MIN_SPIKES,MAX_SPIKES);
	mins->push_back(_max(spike_min,MIN_SPIKES));
	maxs->push_back(_min(spike_max,MAX_SPIKES));
	//rocks (5)
	fixPar(&rock_min,&rock_max,MIN_ROCKS,MAX_ROCKS);
	mins->push_back(_max(rock_min,MIN_ROCKS));
	maxs->push_back(_min(rock_max,MAX_ROCKS));
	//bonuses (6)
	fixPar(&bonus_min,&bonus_max,MIN_BONUSES,MAX_BONUSES);
	mins->push_back(_max(bonus_min,MIN_BONUSES));
	maxs->push_back(_min(bonus_max,MAX_BONUSES));
}

//Resuelve con los parametros dados lo que tiene que hacer		
vector<terna_t*>* Ubicador::generarTernas(int LvLen){
	LvLen -= ESPACIO_FINAL;//para que en los ultimos 300 no tenga nada
	vector<terna_t*>* ternas = new vector<terna_t*>();
	vector<float>* tierraI = new vector<float>();
	vector<float>* tierraD = new vector<float>();
	vector<float>* aireI = new vector<float>();
	vector<float>* aireD = new vector<float>();
	aireI->push_back(0.0);
	aireD->push_back(300.0); //espacio para los jugadores		
	tierraI->push_back(0.0);
	tierraD->push_back(300.0); //espacio para los jugadores	
	int cantidad, mx, mn;
	terna_t* t;
	float x_aux;
	//primero piedras
	mn = mins->at(5);
	mx = maxs->at(5);
	if (mx==mn){
		cantidad=mn;
	}	
	else if (mx > mn){
		cantidad = rand() % (mx-mn);
		cantidad+=mn;
	}
	else{
		cantidad = rand() % (mn-mx);
		cantidad+=mx;		
	}
	if (cantidad > 5 && LvLen < 6000){
		cantidad /= 2;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=ROCK;
		t->id = i;
		t->y = Y_PIEDRA;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(estaLibre(tierraI,tierraD,x_aux-ROCK_SPACE,x_aux+ROCK_WIDTH+ROCK_SPACE)){ 
				t->x = x_aux;
				tierraI->push_back(x_aux-ROCK_SPACE);
				tierraD->push_back(x_aux+ROCK_WIDTH+ROCK_SPACE);
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora pinches
	mn = mins->at(4);
	mx = maxs->at(4);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 3 && LvLen < 6000){
		cantidad = 3;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=SPIKE;
		t->id = i;
		t->y = Y_PINCHE;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(estaLibre(tierraI,tierraD,x_aux-10,x_aux+SPIKE_WIDTH+SPIKE_SPACE)){ 
				t->x = x_aux;
				tierraI->push_back(x_aux-10);
				tierraD->push_back(x_aux+SPIKE_WIDTH+SPIKE_SPACE);
				aireI->push_back(x_aux-20);//20 es un numero magico
				aireD->push_back(x_aux+SPIKE_WIDTH+20);
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora bonuses
	mn = mins->at(6);
	mx = maxs->at(6);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 3 && LvLen < 6000){
		cantidad = 3;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=BONUS;
		t->id = i;
		t->y = Y_BONUS;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(estaLibre(tierraI,tierraD,x_aux-10,x_aux+BONUS_WIDTH+BONUS_SPACE)){ 
				t->x = x_aux;
				tierraI->push_back(x_aux-10);
				tierraD->push_back(x_aux+BONUS_WIDTH+BONUS_SPACE);
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora cangrejos
	mn = mins->at(1);
	mx = maxs->at(1);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 6 && LvLen < 6000){
		cantidad = 6;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=CRAB;
		t->id = i;
		t->y = Y_CANGREJO;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(estaLibre(tierraI,tierraD,x_aux-10,x_aux+CRAB_WIDTH+CRAB_SPACE)){ 
				t->x = x_aux;
				tierraI->push_back(x_aux-10);
				tierraD->push_back(x_aux+CRAB_WIDTH+CRAB_SPACE);
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora peces
	mn = mins->at(3);
	mx = maxs->at(3);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 10 && LvLen < 6000){
		cantidad = 10;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=FISH;
		t->id = i;
		t->y = Y_PEZ;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(cantidad-i >= 3 && estaLibre(tierraI,tierraD,x_aux-10,x_aux+FISH_WIDTH*3+FISH_SPACE*3)){//si hay para 3 pongo un grupo de 3
				t->x = x_aux;
				tierraI->push_back(x_aux-10);
				tierraD->push_back(x_aux+FISH_WIDTH*3+FISH_SPACE*3);
				ternas->push_back(t);
				
				x_aux += FISH_WIDTH+20;
				t = new terna_t;
				t->tipo=FISH;
				t->id = ++i;
				t->y = Y_PEZ;
				t->x = x_aux;
				ternas->push_back(t);

				x_aux += FISH_WIDTH+20;
				t = new terna_t;
				t->tipo=FISH;
				t->id = ++i;
				t->y = Y_PEZ;
				t->x = x_aux;
				ternas->push_back(t);

				break;
			}
			else if(estaLibre(tierraI,tierraD,x_aux-10,x_aux+FISH_WIDTH+FISH_SPACE)){ 
				t->x = x_aux;
				tierraI->push_back(x_aux-10);
				tierraD->push_back(x_aux+FISH_WIDTH+FISH_SPACE);
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora monedas
	mn = mins->at(0);
	mx = maxs->at(0);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 10 && LvLen < 6000){
		cantidad = 10;
	}
	float y_aux;
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=COIN;
		t->id = i;
		x_aux=0.0;
		y_aux=475.0; //altura casi al piso de la moneda (485 es en el piso)
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(cantidad-i >= 5){  //si hay para 5 pongo un grupo de 5
				if(!estaLibre(tierraI,tierraD,x_aux-COIN_SPACE,x_aux+COIN_WIDTH*5+COIN_SPACE*6)){
					y_aux= 295.0;
					aireI->push_back(x_aux-COIN_SPACE);
					aireD->push_back(x_aux+COIN_WIDTH*5+COIN_SPACE*6);
				}
				t->x = x_aux;
				t->y = y_aux;
				ternas->push_back(t);

				for (int mon = 1; mon < 5; mon++){
					x_aux+= COIN_WIDTH+COIN_SPACE;
					t = new terna_t;
					t->tipo=COIN;
					t->id = ++i;
					t->y = y_aux;
					t->x = x_aux;
					ternas->push_back(t);
				}
				break;
			}
			else{
				if(!estaLibre(tierraI,tierraD,x_aux-10,x_aux+COIN_WIDTH+COIN_SPACE)){ 
					y_aux = 295.0;
					aireI->push_back(x_aux-10);
					aireD->push_back(x_aux+COIN_WIDTH+COIN_SPACE);
				}
				t->x = x_aux;
				t->y = y_aux;
				ternas->push_back(t);
				break;
			}
		}
	}
	//ahora las moscas, que no les importa donde esta ubicado lo de tierra
	mn = mins->at(2);
	mx = maxs->at(2);
	cantidad = rand() % (mx-mn);
	cantidad+=mn;
	if (cantidad > 6 && LvLen < 6000){
		cantidad = 6;
	}
	for (int i = 0; i < cantidad; i++){
		t = new terna_t;
		t->tipo=FLY;
		t->id = i;
		t->y = Y_MOSCA;
		x_aux=0.0;
		for (int asd = 0; asd < MAX_ITERS ; asd++){//intenta hasta MAX_ITERS veces acomodarlo, sino no lo pone
			//la magia			
			x_aux = rand() % (LvLen - 300) + 300.0;
			if(estaLibre(aireI,aireD,x_aux-10,x_aux+FLY_WIDTH+FLY_SPACE)){
				if(estaLibre(tierraI,tierraD,x_aux-10,x_aux+FLY_WIDTH+FLY_SPACE)){
					t->y = rand() % 200 + Y_MOSCA; //entre 225 y 425 
				}
				t->x = x_aux;
				aireI->push_back(x_aux-10);
				aireD->push_back(x_aux+FLY_WIDTH+FLY_SPACE);
				ternas->push_back(t);
				break;
			}
		}
	}
	
	return ternas;
}
