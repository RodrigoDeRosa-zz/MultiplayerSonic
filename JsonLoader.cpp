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


#define JSONLOADER_PARAM_NOT_FOUND_MSG "No se encontro el parametro "
#define JSONLOADER_PARAM_NOT_INT_MSG "No se reconoce como entero el parametro "
#define JSONLOADER_PARAM_NOT_POS_MSG "No es positivo el parametro "
#define JSONLOADER_PARAM_NOT_STR_MSG "No se reconoce como cadena el parametro "
#define DEFAULT_PATH "ejemplo.json"

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
	
	
	ifstream in(ruta);
	Json::Value json;

	if(in.fail()){
		Logger::getInstance().log("No se encontro el archivo .json",BAJO);
		in.clear();
		in.open(DEFAULT_PATH);
	}
	in >> json;
	this->setWindow(json);
	this->setRenderer();
	this->stage = this->setStage(json);
}


Stage* JsonLoader::setStage(Json::Value json){
    Stage* stage = new Stage();

	stage->setDimensiones(this->getPositiveInt(json["escenario"]["dimensiones"]["ancho"],"[escenario][dimensiones][ancho]",Window::getInstance().getWidth()*2),
							this->getPositiveInt(json["escenario"]["dimensiones"]["alto"],"[escenario][dimensiones][alto]",Window::getInstance().getHeight()*2));

	if(this->validateValue(json["escenario"]["capas"],"[escenario][capas]")){

		int i = 0;
		for(Json::Value::iterator it = json["escenario"]["capas"].begin(); it != json["escenario"]["capas"].end(); it++){
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

	SpriteGroup* activeSprites = new SpriteGroup();

	this->checkNullValue(json["escenario"]["entidades"]);

	int contadorEntidades = 0;
	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {

		Bloque* bloque;
		Circulo* circulo;
		
		int x = this->getPositiveInt((*it)["coordenada"]["x"],string("[escenario][entidades]") + string("[coordenada][x]"),-1);
		int y = this->getPositiveInt((*it)["coordenada"]["y"],string("[escenario][entidades]") +  string("[coordenada][y]"),-1);
		
		vector<int> color = this->getColor((*it)["color"],"[escenario][entidades][color]");
		
		if(x<0 || y<0){
			Logger::getInstance().log("No se creo el sprite");
			continue;
		}

		if((*it)["circulo"].asBool()){
			int r = this->getPositiveInt((*it)["radio"],string("[escenario][entidades]") + string("[radio]"),-1);
			if(r < 0){
				Logger::getInstance().log("No se creo el sprite");
				continue;
			}
			circulo = new Circulo(x, y, r);
			circulo->setBackgroundColor(color[0],color[1],color[2]);
			activeSprites->add(circulo);
		}
		else{
			int h = this->getPositiveInt((*it)["dimensiones"]["alto"],string("[escenario][entidades]") + string("[dimensiones][alto]"),-1);
			int w = this->getPositiveInt((*it)["dimensiones"]["ancho"],string("[escenario][entidades]") + string("[dimensiones][ancho]"),-1);
			if(h<0 || w<0){
				Logger::getInstance().log("No se creo el sprite");
				continue;
			}
			bloque = new Bloque(x, y, h, w);
			bloque->setBackgroundColor(color[0],color[1],color[2]);
			activeSprites->add(bloque);
		}
		contadorEntidades++;
	}

	vector<Sprite*> vectorSprites = activeSprites->getSprites();

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		Texture* texture = new Texture();
		texture->loadFromFile(getString((*it)["ruta"],"[escenario][texturas][ruta]"));

		for(Json::Value::iterator idIt = (*it)["ids"].begin();idIt != (*it)["ids"].end();idIt++){
			int spriteIndex = (*idIt).asInt();
			if((*idIt).asInt() >= vectorSprites.size()) continue;
			if(dynamic_cast<Circulo*>(vectorSprites[spriteIndex]) != NULL) {
				((Circulo*)vectorSprites[spriteIndex])->setTexture((*it)["ruta"].asString());
				continue;
			}
			vectorSprites[(*idIt).asInt()]->setTexture(texture);
		}
	}

	return activeSprites;
}

void JsonLoader::setWindow(Json::Value json){

	Window::getInstance().setDimensions(json["ventana"]["dimensiones"]["ancho"].asInt(), json["ventana"]["dimensiones"]["alto"].asInt());
    Window::getInstance().init();
}

int JsonLoader::getPositiveInt(Json::Value json, string where, int defaultValue, bool zero){
	int value;
	if(!(this->validateValue(json,where)) || !isInteger(json,where) || !isPositiveInteger(json,where)){
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

bool JsonLoader::fileExists(string path){
	return true;
}

void JsonLoader::setRenderer(){
	Renderer::getInstance().init();
    Renderer::getInstance().setDrawColor(0xFF, 0xFF, 0xFF, 0x01);
}

Stage* JsonLoader::getStage(){
	return this->stage;
}

camara* JsonLoader::getCamara(){
	int velocidad = 1;
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

bool JsonLoader::validateValue(Json::Value json, string where){
	bool valid = true;
	if(this->checkNullValue(json)){
		Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_FOUND_MSG) + where,MEDIO);
		valid = false;
	}
	return valid;
}

vector<int> JsonLoader::getColor(Json::Value json, string where){
	string color = getString(json,where,"verde");
	vector<int> colorRGB = colores[color];
	return colorRGB;
}
