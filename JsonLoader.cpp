#include "JsonLoader.hpp"
#include <fstream>
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Layer.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Sprite.hpp"
#include <SDL2/SDL.h>
#include "Graficos/Renderer.hpp"
#include "Graficos/Window.hpp"

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

	this->checkNullValue(json["escenario"]["capas"]);

	for(Json::Value::iterator it = json["escenario"]["capas"].begin(); it != json["escenario"]["capas"].end(); it++){
    	Layer* layer = new Layer();

		layer->setTexPath(this->getString((*it)["ruta_imagen"]));
		layer->loadImage();
		layer->setIndexZ(this->getPositiveInt((*it)["index_z"]));

		stage->addLayer(layer);
	}

    /*Se agregan al grupo de sprites*/
    SpriteGroup* activeSprites = this->getSprites(json);

    /*Se define el sprite group del escenario como el creado recien*/
    stage->setSpriteGroup(activeSprites);

    return stage;
}

SpriteGroup* JsonLoader::getSprites(Json::Value json){

	SpriteGroup* activeSprites = new SpriteGroup();

	this->checkNullValue(json["escenario"]["entidades"]);

	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {

		//hay que chequear el tema de la velocidad de los sprites

		Sprite* sprite = new Sprite(this->getPositiveInt((*it)["coordenada"]["x"]), this->getPositiveInt((*it)["coordenada"]["y"]),
									this->getPositiveInt((*it)["dimensiones"]["alto"]),  this->getPositiveInt((*it)["dimensiones"]["ancho"]));
		sprite->setBackgroundColor(255,130,15);
		activeSprites->add(sprite);
	}

	vector<Sprite*> vectorSprites = activeSprites->getSprites();

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		//hay que chequear el tema de la velocidad de los sprites

		Texture* texture = new Texture();
		texture->loadFromFile((*it)["ruta"].asString());

		for(Json::Value::iterator idIt = (*it)["ids"].begin();idIt != (*it)["ids"].end();idIt++){
			vectorSprites[(*idIt).asInt()]->setTexture(texture);
		}
	}

	return activeSprites;
}

void JsonLoader::setWindow(Json::Value json){

	Window::getInstance().setDimensions(this->getPositiveInt(json["ventana"]["dimensiones"]["ancho"]), this->getPositiveInt(json["ventana"]["dimensiones"]["alto"]));
    Window::getInstance().init();
}

int JsonLoader::getPositiveInt(Json::Value json){
	this->checkNullValue(json);
	if(!json.isInt() || (json.asInt() <= 0)){
		//handle
	}
	return json.asInt();
}

void JsonLoader::checkNullValue(Json::Value json){
	if(json == Json::nullValue){
		//no encontro la clave, levantar excepcion
	}
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
