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
#include <stdlib.h>


#define JSONLOADER_PARAM_NOT_FOUND_MSG "No se encontro el parametro "
#define JSONLOADER_PARAM_NOT_INT_MSG "No se reconoce como entero el parametro "
#define JSONLOADER_PARAM_NOT_POS_MSG "No es positivo el parametro "
#define DEFAULT_PATH "ejemplo.json"
using namespace std;

JsonLoader::JsonLoader(char* ruta){
	int verde[]= {0,204,0};
	colores["verde"] = verde;
	ifstream in(ruta);
	Json::Value json;

	if(in.fail()){
		Logger::getInstance().log("No se encontro el archivo .json");
		//in.close();
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

			layer->setTexPath(this->getString((*it)["ruta_imagen"]));
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

		if((*it)["circulo"].asBool()){
			circulo = new Circulo(((*it)["coordenada"]["x"]).asInt(), ((*it)["coordenada"]["y"]).asInt(),
			(*it)["radio"]["r"].asInt());
			circulo->setTexture("Graficos/index.png");
			activeSprites->add(circulo);
		}
		else{
			bloque = new Bloque((*it)["coordenada"]["x"].asInt(), (*it)["coordenada"]["y"].asInt(),(*it)["dimensiones"]["alto"].asInt(),(*it)["dimensiones"]["ancho"].asInt());
			bloque->setBackgroundColor(255,130,15);
			activeSprites->add(bloque);}

		/*int x = this->getPositiveInt((*it)["coordenada"]["x"],string("[escenario][entidades]") + string("[coordenada][x]"),-1);
		int y = this->getPositiveInt((*it)["coordenada"]["y"],string("[escenario][entidades]") +  string("[coordenada][y]"),-1);

		if(x<0 || y<0){
			Logger::getInstance().log("No se creo el sprite");
			continue;
		}

		sprite = new Bloque((*it)["coordenada"]["x"].asInt(), (*it)["coordenada"]["y"].asInt(),(*it)["dimensiones"]["ancho"].asInt(),(*it)["dimensiones"]["alto"].asInt());
		sprite->setBackgroundColor(255,130,15);
		sprite->setIndexZ((*it)["index_z"].asInt());
		activeSprites->add(sprite);

		if((*it)["circulo"].asBool()){
			circulo = new Circulo(x, y,(*it)["radio"]["r"].asInt());
			circulo->setTexture("Graficos/index.png");
			activeSprites->add(circulo);
		}
		else{
			int h = this->getPositiveInt((*it)["dimensiones"]["alto"],string("[escenario][entidades]") + string("[dimensiones][alto]"),-1);
			int w = this->getPositiveInt((*it)["dimensiones"]["ancho"],string("[escenario][entidades]") + string("[dimensiones][ancho]"),-1);
			if(h<0 || w<0){
			Logger::getInstance().log("No se creo el sprite");
			continue;
		}
			bloque = new Bloque(x,y,h,w);
			bloque->setBackgroundColor(255,130,15);
			activeSprites->add(bloque);
		}
		contadorEntidades++;*/
	}

	vector<Sprite*> vectorSprites = activeSprites->getSprites();

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		Texture* texture = new Texture();
		texture->loadFromFile((*it)["ruta"].asString());

		for(Json::Value::iterator idIt = (*it)["ids"].begin();idIt != (*it)["ids"].end();idIt++){
			if((*idIt).asInt() >= vectorSprites.size())continue;
			vectorSprites[(*idIt).asInt()]->setTexture(texture);
		}
	}

	return activeSprites;
}

void JsonLoader::setWindow(Json::Value json){

	Window::getInstance().setDimensions(json["ventana"]["dimensiones"]["ancho"].asInt(), json["ventana"]["dimensiones"]["alto"].asInt());
    Window::getInstance().init();
}

int JsonLoader::getPositiveInt(Json::Value json, string where, int defaultValue){
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

bool isPositiveInteger(Json::Value json, string where){
	if (json.asInt() > 0) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_POS_MSG) + where);
	return false;
}

bool isInteger(Json::Value json, string where){
	if (json.isInt()) return true;
	Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_INT_MSG) + where);
	return false;
}

string JsonLoader::getString(Json::Value json){

	if(!json.isString() || (json.asString() == "")){
		//handle
	}
	return json.asString();
}

bool fileExists(string path){
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
		//printf("No se encontro la clave %s \n",where);
		Logger::getInstance().log(string(JSONLOADER_PARAM_NOT_FOUND_MSG) + where);
		valid = false;
	}
	return valid;
}
