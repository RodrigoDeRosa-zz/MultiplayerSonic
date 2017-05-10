enum key_event {LEFT,RIGHT,SPACE,QUIT};


//InMessage
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
