#include "Graficos/Window.hpp"
#include "Graficos/Stage.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include "Graficos/SpriteGroup.hpp"
#include "Graficos/SpriteGroup.hpp"

using namespace std;

class JsonLoader{
	Stage* stage;
	public:
		JsonLoader(char* ruta);
		Stage* getStage();
		camara* getCamara();
	private:
		Stage* setStage(Json::Value json);
		SpriteGroup* getSprites(Json::Value json);
		void setWindow(Json::Value json);
		void setRenderer();
		int getPositiveInt(Json::Value json);
		void checkNullValue(Json::Value json);
		string getString(Json::Value json);
		
};
