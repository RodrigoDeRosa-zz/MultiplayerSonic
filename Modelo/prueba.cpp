#include "Model.hpp"
#include <stdio.h>
//#include "Player.hpp"

using namespace std;

void printFloatVector(vector<float> vector);

int main(int argc, char** argv){
	Model* model = new Model();
	model->addPlayer("player1");
	Player* player = model->getPlayer("player1");
	printf("Player Address: *%p* \n",player);
	printf("Player Name: *%s* \n",player->getName().c_str());
}

void printFloatVector(vector<float> vector){
	for(int i=0; i<vector.size(); i++) printf("vector[%d]: %f \n",i,vector[i]);
}
