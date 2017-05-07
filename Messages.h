enum key_event {LEFT,RIGHT,SPACE};

typedef struct in_message{
	char* playerName;
	bool connection; //si no se puede bool, char
	key_event key;
}InMessage;

typedef struct out_message{
	char* playerName;
	bool connection; //si no se puede bool, char
	float dirX;
	float dirY;
	float posX;
	float posY;
}OutMessage;
