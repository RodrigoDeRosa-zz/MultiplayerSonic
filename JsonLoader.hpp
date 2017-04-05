#include "Graficos/Window.hpp"
#include "Graficos/Stage.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include "Graficos/SpriteGroup.hpp"
#include "Graficos/SpriteGroup.hpp"
#include <map>
#include <vector>

using namespace std;


class JsonLoader{
	camara* camaraPantalla;
	Stage* stage;
	map<string,vector<int> > colores;
	Stage* setStage(Json::Value json);
	SpriteGroup* getSprites(Json::Value json);
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
	camara* setCamara(Json::Value json);
	vector<int> getColor(Json::Value json, string where);
	public:
		JsonLoader(char* ruta);
		Stage* getStage();
		camara* getCamara();

};
