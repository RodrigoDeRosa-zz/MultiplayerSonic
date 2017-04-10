#include "JsonLoader.hpp"
#include <fstream>
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Layer.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Sprite.hpp"
#include <SDL2/SDL.h>
#include "Graficos/Renderer.hpp"
#include "Graficos/Window.hpp"
#include "Graficos/Camara.hpp"
#include "Graficos/Bloque.hpp"
#include "Graficos/Circulo.hpp"
#include "Logger2.hpp"
#include <map>
#include <vector>
#include <stdlib.h>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define JSONLOADER_SPRITE_NOCREAT_MSG "No se creo el sprite"
#define JSONLOADER_PARAM_NOT_FOUND_MSG "No se encontro el parametro "
#define JSONLOADER_PARAM_NOT_INT_MSG "No se reconoce como entero el parametro "
#define JSONLOADER_PARAM_NOT_POS_MSG "No es positivo el parametro "
#define JSONLOADER_PARAM_NOT_STR_MSG "No se reconoce como cadena el parametro "
#define JSONLOADER_PARAM_NOT_ARRAY_MSG "No se reconoce como array el parametro "
#define JSONLOADER_PARAM_NOT_BOOL_MSG "No se reconoce como booleano el parametro "
#define JSONLOADER_PARAM_NOT_CLR_MSG "No se reconoce como color al string "
#define INVALID_LOG_LVL_MSG "Nivel de log invalido. (Seteado en bajo)"
#define DEFAULT_PATH "ejemplo2.json"
#define DEFAULT_WIDTH 1200
#define DEFAULT_HEIGHT 640
#define DEFAULT_STAGE_WIDHT 3600
#define DEFAULT_STAGE_HEIGHT 640
#define DEFAULT_IMAGE "Graficos/question.png"

using namespace std;

int verdeRGB[]= {0,204,0};
vector<int> verde (verdeRGB, verdeRGB + sizeof(verdeRGB) / sizeof(int) );
int rojoRGB[]= {204,0,0};
vector<int> rojo (rojoRGB, rojoRGB + sizeof(rojoRGB) / sizeof(int) );
int azulRGB[]= {0,0,204};
vector<int> azul (azulRGB, azulRGB + sizeof(azulRGB) / sizeof(int) );
int amarilloRGB[]= {255,255,0};
vector<int> amarillo (amarilloRGB, amarilloRGB + sizeof(amarilloRGB) / sizeof(int) );

int violetaRGB[]= {102,0,102};
vector<int> violeta (violetaRGB, violetaRGB + sizeof(violetaRGB) / sizeof(int) );


JsonLoader::JsonLoader(char* ruta){

	(colores["verde"]) = verde;
	(colores["rojo"]) = rojo;
	(colores["azul"]) = azul;
	(colores["amarillo"]) = amarillo;
	(colores["violeta"]) = violeta;

    //carga el .json
	ifstream in(ruta);
	Json::Value json;

    //no encuentra el archivo
	if(in.fail()){
		Logger::getInstance().log("No se encontro el archivo .json",BAJO);
		in.clear();
		in.open(DEFAULT_PATH);
	}

    //hay un error de sintaxis
	try{
		in >> json;
	}catch(const Json::RuntimeError& e){
		Logger::getInstance().log(string("Error de sintaxis en el archivo .json . Error: \n") + string(e.what()),BAJO);
		ifstream input(DEFAULT_PATH);
		input >> json;
	}
    this->setLogger(json);
	this->setWindow(json);
	this->setRenderer();
	this->stage = this->setStage(json);
	this->camaraPantalla = this->setCamara(json);
}

void JsonLoader::setLogger(Json::Value json){
    string level = getString(json["log_lvl"],"[log_lvl]","bajo");
    if (level == "bajo") Logger::getInstance().setLogLevel(BAJO);
    else if (level == "medio") Logger::getInstance().setLogLevel(MEDIO);
    else if (level == "alto") Logger::getInstance().setLogLevel(ALTO);
    else Logger::getInstance().setLogLevel(BAJO);
}

Stage* JsonLoader::setStage(Json::Value json){
    Stage* stage = new Stage();

    this->validateValue(json["escenario"],"[escenario]");

	stage->setDimensions(this->getPositiveInt(json["escenario"]["dimensiones"]["ancho"],"[escenario][dimensiones][ancho]",DEFAULT_STAGE_WIDHT),
							this->getPositiveInt(json["escenario"]["dimensiones"]["alto"],"[escenario][dimensiones][alto]",DEFAULT_STAGE_HEIGHT));

	if(this->validateValue(json["escenario"]["capas"],"[escenario][capas]")){

		int i = 0;
		for(Json::Value::iterator it = json["escenario"]["capas"].begin(); it != json["escenario"]["capas"].end(); it++){
			if(i==2) break; //no hay mas de dos capas
			Layer* layer = new Layer();

			layer->setTexPath(this->getString((*it)["ruta_imagen"],"[escenario][capas][ruta_imagen]"));
			layer->setDimensions( stage->getWidth(), stage->getHeight());
			layer->loadImage();
			layer->setIndexZ(this->getPositiveInt((*it)["index_z"],"[escenario][capas][index_z]",i));

			stage->addLayer(layer);
			i++;
		}
	}

    SpriteGroup* activeSprites = this->getSprites(json);

    stage->setSpriteGroup(activeSprites);

    return stage;
}

SpriteGroup* JsonLoader::getSprites(Json::Value json){
	this->validateValue(json["escenario"]["texturas"],"[escenario][texturas]");

	int contadorTexturas = 0;

	map<string,Texture*> texturas;

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		string contador = SSTR( contadorTexturas );

        //la ruta no es una cadena
		if(getString((*it)["ruta"],string("[escenario][texturas][") + contador + string("][ruta]")) == string("")) {
			contadorTexturas++;
			continue;
		}
		string ruta = getString((*it)["ruta"],string("[escenario][texturas][") + contador + string("][ruta]"));
		Texture* texture = new Texture();

        //la ruta no es valida
		if(!(texture->loadFromFile(ruta)))
            texture->loadFromFile(DEFAULT_IMAGE);
		texturas[ruta] = texture;
	}

	SpriteGroup* activeSprites = new SpriteGroup();

	this->validateValue(json["escenario"]["entidades"],"[escenario][entidades]");

	int contadorEntidades = 0;

	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {

		Bloque* bloque;
		Circulo* circulo;

		string contador = SSTR( contadorEntidades );

		int x = this->getPositiveInt((*it)["coordenada"]["x"],string("[escenario][entidades][") + contador + string("][coordenada][x]"),-1,true);
		int y = this->getPositiveInt((*it)["coordenada"]["y"],string("[escenario][entidades][") + contador + string("][coordenada][y]"),-1,true);

		vector<int> color = this->getColor((*it)["color"],string("[escenario][entidades][") + contador + string("][color]"));
		string imagen = getString((*it)["imagen"],string("[escenario][entidades][") + contador + string("][imagen]"));

		if(x<0 || y<0){
			Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
			continue;
		}

        //chequeo que el parametro "circulo" exista y sea bool
		bool binarioCirculo = validateValue((*it)["circulo"],string("[escenario][entidades][") + contador + string("][circulo]"))
			 && isBool((*it)["circulo"],string("[escenario][entidades][") + contador + string("][circulo]"));

		if(binarioCirculo && (*it)["circulo"].asBool()){
			int r = this->getPositiveInt((*it)["radio"],string("[escenario][entidades][") + contador + string("][radio]"),-1);
			if(r < 0){
				Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
				continue;
			}
			circulo = new Circulo(x, y, r);
			circulo->setBackgroundColor(color[0],color[1],color[2]);
			circulo->setIndexZ(this->getPositiveInt((*it)["index_z"],string("[escenario][entidades][") + contador + string("][index_z]"), 0));
            //la ruta no es valida
			if(!(circulo->setTexture(imagen)))
                circulo->setTexture(DEFAULT_IMAGE);
			activeSprites->add(circulo);
		}
		else if(binarioCirculo){
			int h = this->getPositiveInt((*it)["dimensiones"]["alto"],string("[escenario][entidades][") + contador + string("][dimensiones][alto]"),-1);
			int w = this->getPositiveInt((*it)["dimensiones"]["ancho"],string("[escenario][entidades][") + contador + string("][dimensiones][ancho]"),-1);
			if(h<0 || w<0){
				Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
				continue;
			}
			bloque = new Bloque(x, y, h, w);
			bloque->setBackgroundColor(color[0],color[1],color[2]);
			bloque->setIndexZ(this->getPositiveInt((*it)["index_z"],string("[escenario][entidades][") + contador + string("][index_z]"), 0));
            if(imagen != string("")){
			    if(texturas.find(imagen) != texturas.end()) bloque->setTexture(texturas[imagen]);
                else{
                    Texture* texture = new Texture();
                    texture->loadFromFile(DEFAULT_IMAGE);
                    bloque->setTexture(texture);
                }
            }
			activeSprites->add(bloque);
		}
		contadorEntidades++;
	}
	return activeSprites;

}

void JsonLoader::setWindow(Json::Value json){
    int width = this->getPositiveInt(json["ventana"]["dimensiones"]["ancho"], string("[ventana][dimensiones][ancho]"), DEFAULT_WIDTH);
    int height = this->getPositiveInt(json["ventana"]["dimensiones"]["alto"], string("[ventana][dimensiones][alto]"), DEFAULT_HEIGHT);

	Window::getInstance().setDimensions(width, height);
    Window::getInstance().init();
}

int JsonLoader::getPositiveInt(Json::Value json, string where, int defaultValue, bool zero){
	int value;
	if(!(this->validateValue(json,where)) || !isInteger(json,where) || !isPositiveInteger(json,where,zero)){
		value = defaultValue;
	}
	else
		value = json.asInt();
	return value;
}

bool JsonLoader::checkNullValue(Json::Value json){
	return (json == Json::nullValue);
}

bool JsonLoader::isPositiveInteger(Json::Value json, string where, bool zero){
	if (json.asInt() > 0) return true;
	if (zero && json.asInt() == 0) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_POS_MSG) + where,MEDIO);
	return false;
}

bool JsonLoader::isInteger(Json::Value json, string where){
	if (json.isInt()) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_INT_MSG) + where,MEDIO);
	return false;
}

string JsonLoader::getString(Json::Value json, string where, string defaultValue){

	if(!this->validateValue(json,where) || !this->isString(json,where)){
		return defaultValue;
	}
	return json.asString();
}

bool JsonLoader::isString(Json::Value json, string where){
	if (json.isString()) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_STR_MSG) + where,MEDIO);
	return false;
}

void JsonLoader::setRenderer(){
	Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);
}

Stage* JsonLoader::getStage(){
	return this->stage;
}

camara* JsonLoader::setCamara(Json::Value json){
	int velocidad = getPositiveInt(json["vel_scroll"],"[vel_scroll]",1);
	camara* camara_pantalla = new camara(0,0,velocidad,Window::getInstance().getWidth(),Window::getInstance().getHeight(),(this->stage)->getWidth(), (this->stage)->getHeight() );
	Apuntado* seguido = new Apuntado(0, 0, 30, 30,velocidad);
    Texture* invisible = new Texture();
	invisible->setDimensions(30, 30);
    invisible->setKeyColor(0,0,0);
    seguido->setBackgroundColor(0, 0, 0);
    seguido->setTexture(invisible);
    camara_pantalla->setApuntado(seguido);
	return camara_pantalla;
}

camara* JsonLoader::getCamara(){
	return this->camaraPantalla;
}

bool JsonLoader::validateValue(Json::Value json, string where){
	bool valid = true;
	if(this->checkNullValue(json)){
		Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_FOUND_MSG) + where,MEDIO);
		valid = false;
	}
	return valid;
}

bool JsonLoader::isArray(Json::Value json, string where){
	if (json.isArray()) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_ARRAY_MSG) + where,MEDIO);
	return false;
}

bool JsonLoader::isBool(Json::Value json, string where){
	if (json.isBool()) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_BOOL_MSG) + where,MEDIO);
	return false;
}

vector<int> JsonLoader::getColor(Json::Value json, string where){
  string color = getString(json,where,"verde");
  vector<int> colorRGB = colores[color];
  if (colorRGB.empty()){
      Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_CLR_MSG) + where,MEDIO);
      colorRGB = colores["verde"];
      return colorRGB;
  }
	return colorRGB;
}
