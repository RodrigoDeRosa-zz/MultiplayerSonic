#include "Messages.h"



char* getPlayerName(InMessage* in){
	return in->playerName;
}

bool getConnection(InMessage* in){
	return in->connection;
}

key_event getKey(InMessage* in){
	return in->key;
}

void setPlayerName(InMessage* in, char* playerName){
	in->playerName = playerName;
}

void setConnection(InMessage* in, bool connection){
	in->connection = connection;
}

void setKey(InMessage* in, key_event key){
	in->key = key;
}




char* getPlayerName(OutMessage* out){
	return out->playerName;
}

bool getConnection(OutMessage* out){
	return out->connection;
}

float getDirX(OutMessage* out){
	return out->dirX;
}

float getDirY(OutMessage* out){
	return out->dirY;
}

float getPosX(OutMessage* out){
	return out->posX;
}

float getPosY(OutMessage* out){
	return out->posY;
}

void setPlayerName(OutMessage* out, char* playerName){
	out->playerName = playerName;
}

void setConnection(OutMessage* out, bool connection){
	out->connection = connection;
}

void setDirX(OutMessage* out, float dirX){
	out->dirX = dirX;
}

void setDirY(OutMessage* out, float dirY){
	out->dirY = dirY;
}

void setPosX(OutMessage* out, float posX){
	out->posX = posX;
}

void setPosY(OutMessage* out, float posY){
	out->posY = posY;
}
