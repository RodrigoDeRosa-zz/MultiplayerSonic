#ifndef MESSAGE_HPP
#define MESSAGE_HPP

//KEY_TOTAL se devuelve en caso que la cola este vacia
enum key_event {PING, LEFT, RIGHT, UP, DOWN, SPACE, QUIT, KEY_TOTAL};

typedef struct out_message{
	char* playerName;
	bool connection;
	float dirX;
	float dirY;
	float posX;
	float posY;
} out_message_t;

typedef struct in_message{
    int id;
    key_event key;
} in_message_t;

#endif /*MESSAGE_HPP*/
