#include "../Graficos/Stage.hpp"
#include "../Graficos/Bloque.hpp"
#include "../Graficos/Window.hpp"
#include "json/json.h"
#include "json/json-forwards.h"


using namespace std;


class JsonLoader{
	Camara* camaraPantalla;
	map<string,vector<int> > colores;
	Json::Value json;
    void setJson(char* ruta, char* rutaDefault);
    Layer* getLayer(Json::Value json, int layerNumber,int width, int height);
	SpriteGroup* getSprites(Json::Value json);
    map<string,Texture*> getTextures(Json::Value json);
    Sprite* getSprite(Json::Value json, string contador, map<string,Texture*> texturas);
    Bloque* getBloque(Json::Value json, string contador, int x, int y, string imagen, map<string,Texture*> texturas, vector<int> color);
	void setWindow();
	void setRenderer();
	int getPositiveInt(Json::Value json, string where, int defaultValue, bool zero = false);
	bool checkNullValue(Json::Value json);
	string getString(Json::Value json,string where,string defaultValue = string(""));
	bool validateValue(Json::Value json, string where);
	bool isPositiveInteger(Json::Value json, string where, bool zero = false);
	bool isInteger(Json::Value json, string where);
	bool isString(Json::Value json, string where);
	bool isArray(Json::Value json, string where);
	bool isBool(Json::Value json, string where);
	void setLogger();
	vector<int> getColor(Json::Value json, string where);
	public:
		JsonLoader(char* ruta, char* rutaDefault);
		void setGame();
		Stage* getStage();
		Camara* getCamara(Stage* stage);
		string getPort();
		string getHostname();

};
