
#define PLAYERNAME_LEN 10
#define PINGNAME	"ping"

enum key_event {LEFT,RIGHT,SPACE,QUIT};

static const int PLAYER_NAME_LEN = PLAYERNAME_LEN;

//InMessage
struct in_message{
	char playerName[PLAYERNAME_LEN];
	bool connection; //si no se puede bool, char
	key_event key;
};

typedef struct in_message InMessage;
//Getters
char* getPlayerName(InMessage* in);
bool getConnection(InMessage* in);
key_event getKeyEvent(InMessage* in);
//Setters
void setPlayerName(InMessage* in, char* playerName);
void setConnection(InMessage* in, bool connection);
void setKey(InMessage* in, key_event key);


//OutMessage
struct out_message{
	char playerName[PLAYERNAME_LEN];
	bool connection; //si no se puede bool, char
	float dirX;
	float dirY;
	float posX;
	float posY;
};

typedef struct out_message OutMessage;
//Getters
char* getPlayerName(OutMessage* out);
bool getConnection(OutMessage* out);
float getDirX(OutMessage* out);
float getDirY(OutMessage* out);
float getPosX(OutMessage* out);
float getPosY(OutMessage* out);
//Setters
void setPlayerName(OutMessage* out, char* playerName);
void setConnection(OutMessage* out, bool connection);
void setDirX(OutMessage* out, float dirX);
void setDirY(OutMessage* out, float dirY);
void setPosX(OutMessage* out, float posX);
void setPosY(OutMessage* out, float posY);
