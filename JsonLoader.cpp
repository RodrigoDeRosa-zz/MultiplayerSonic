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

using namespace std;

JsonLoader::JsonLoader(char* ruta){
	ifstream in(ruta);
  	Json::Value json;
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

		for(Json::Value::iterator it = json["escenario"]["capas"].begin(); it != json["escenario"]["capas"].end(); it++){
			Layer* layer = new Layer();

			layer->setTexPath(this->getString((*it)["ruta_imagen"]));
			layer->setDimensions( stage->getWidth(), stage->getHeight());
			layer->loadImage();
			layer->setIndexZ((*it)["index_z"].asInt());

			stage->addLayer(layer);
		}
	}


    SpriteGroup* activeSprites = this->getSprites(json);

    stage->setSpriteGroup(activeSprites);

    return stage;
}

SpriteGroup* JsonLoader::getSprites(Json::Value json){

	SpriteGroup* activeSprites = new SpriteGroup();

	this->checkNullValue(json["escenario"]["entidades"]);

	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {

		Sprite* sprite;

		/*
		if((*it)["circulo"].asBool()){
			sprite = new Circulo(this->getPositiveInt((*it)["coordenada"]["x"]), this->getPositiveInt((*it)["coordenada"]["y"]),
									this->getPositiveInt((*it)["dimensiones"]["radio"]));
		}
		*/

		sprite = new Bloque((*it)["coordenada"]["x"].asInt(), (*it)["coordenada"]["y"].asInt(),(*it)["dimensiones"]["ancho"].asInt(),(*it)["dimensiones"]["alto"].asInt());
		sprite->setBackgroundColor(255,130,15);
		sprite->setIndexZ((*it)["index_z"].asInt());
		activeSprites->add(sprite);
	}

	vector<Sprite*> vectorSprites = activeSprites->getSprites();

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		Texture* texture = new Texture();
		texture->loadFromFile((*it)["ruta"].asString());

		for(Json::Value::iterator idIt = (*it)["ids"].begin();idIt != (*it)["ids"].end();idIt++){
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

	if(!json.isInt() || (json.asInt() < 0) || !(this->validateValue(json,where))){
		value = defaultValue;
	}
	else
		value = json.asInt();
	return value;
}

bool JsonLoader::checkNullValue(Json::Value json){
	return (json == Json::nullValue);
}

string JsonLoader::getString(Json::Value json){
	this->checkNullValue(json);
	if(!json.isString() || (json.asString() == "")){
		//handle
	}
	return json.asString();
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
		printf("No se encontro la clave %s \n",where);
		valid = false;
	}
	return valid;
}
