#include <stdio.h>
#include <string.h>
#include <string>

#include "Ubicador.hpp"


#define LARGO_LV 5000

int main(){
	vector<terna_t*>* v;
	Ubicador* u = new Ubicador();
	u->setParams(1,10,1,10,1,10,1,10,1,10,1,10,1,10);
	v = u->generarTernas(LARGO_LV);
	string s;
	for (auto it = v->begin(); it != v->end(); ++it){
		switch((*it)->tipo){
			case COIN:
				s=string("COIN");break;
			case CRAB:
				s=string("CRAB");break;
			case FLY:
				s=string("FLY");break;
			case FISH:
				s=string("FISH");break;
			case SPIKE:
				s=string("SPIKE");break;
			case ROCK:
				s=string("ROCK");break;
			case BONUS:
				s=string("BONUS");break;
			default:
				s=string("basura");break;
		}
		printf("%s con X=%.2f,Y=%.2f,id=%d\n",s.c_str(),(*it)->x,(*it)->y,(*it)->id);
	}
	return 0;
}
