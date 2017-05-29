#ifndef MESSAGE_HPP
#define MESSAGE_HPP

//KEY_TOTAL se devuelve en caso que la cola este vacia
enum message_type{PINGO, GAME_SET, GAME_START, PLAYER_UPDATE, PLAYER_SET, ROCK_SET, SPIKE_SET, COIN_SET, COIN_UPDATE, BONUS_SET,  BONUS_UPDATE,
	FISH_SET, FISH_UPDATE, FLY_SET, FLY_UPDATE, CRAB_SET, CRAB_UPDATE, MESSAGE_TOTAL};
enum key_event {PING, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN, SPACE_UP, SPACE_DOWN, DOWN_DOWN,DOWN_UP, QUIT, RECONNECTION, KEY_TOTAL};
enum move_type{IDLED, IDLEI, JUMPD, JUMPI, RUND, RUNI, WALKD, WALKI, WAITD, WAITI, BRAKED, BRAKEI, BALLD, BALLI, DMGD, DMGI, CROUCHD, CROUCHI,ROLLI,ROLLD,CRABL,CRABD,FLYL,FLYD,FISHU,FISHD,MOVE_TOTAL};
//IDLE es parado
//JUMP es saltando
//RUN es corriendo
//WALK es caminando
//WAIT es cuando te apura porque estuvo esperando (no es un caso particular de IDLE?)
//BRAKE es cuando venia corriendo y frena
//BALL es la bolita **NO SE USA**
//DMG es cuando lo lastiman
//CROUCH es agachado **NO SE USA**
//ROLL es cuando rueda
typedef struct out_message{
	message_type ping; //En 1 indica que el mensaje es un ping del servidor
	int id;
	bool connection;
	float posX;
	float posY;
	float camPos;
	move_type move;
	int frame;
} out_message_t;

typedef struct in_message{
    int id;
    key_event key;
} in_message_t;

#endif /*MESSAGE_HPP*/
