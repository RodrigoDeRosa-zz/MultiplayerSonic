#include "Graficos/Window.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Circulo.hpp"
#include "Graficos/Bloque.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include "Graficos/SpriteGroup.hpp"
#include "Graficos/SpriteGroup.hpp"
#include <map>
#include <vector>

using namespace std;


class JsonLoader{
	Camara* camaraPantalla;
	Stage* stage;
	map<string,vector<int> > colores;
    Json::Value getJson(char* ruta);
	Stage* setStage(Json::Value json);
    Layer* getLayer(Json::Value json, int layerNumber,int width, int height);
	SpriteGroup* getSprites(Json::Value json);
    map<string,Texture*> getTextures(Json::Value json);
    Sprite* getSprite(Json::Value json, string contador, map<string,Texture*> texturas);
    Circulo* getCirculo(Json::Value json, string contador, int x, int y, string imagen, map<string,Texture*> texturas, vector<int> color);
    Bloque* getBloque(Json::Value json, string contador, int x, int y, string imagen, map<string,Texture*> texturas, vector<int> color);
	void setWindow(Json::Value json);
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
	void setLogger(Json::Value);
	Camara* setCamara(Json::Value json);
	vector<int> getColor(Json::Value json, string where);
	public:
		JsonLoader(char* ruta);
		Stage* getStage();
		Camara* getCamara();

};
