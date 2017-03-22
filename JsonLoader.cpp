//#include <json/json.h>
#include <SDL2/SDL.h>
#include "JsonLoader.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include <fstream>

using namespace std;

JsonLoader::JsonLoader(char* ruta){
	ifstream in(ruta);
  	Json::Value json;
  	in >> json;
	//Create window
	this->ventana = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, json["ventana"]["dimensiones"]["ancho"].asInt(), json["ventana"]["dimensiones"]["alto"].asInt(), SDL_WINDOW_SHOWN );
	if( !this->ventana ){
		printf( "La ventana no pudo ser creada! SDL Error: %s\n", SDL_GetError() );
	}
	//creo los sprites
	this->sprites = SpriteGroup();
	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {
		int x = (*it)["coordenada"]["x"].asInt();
		printf("%d \n",x);
		int y = (*it)["coordenada"]["y"].asInt();
		int h = (*it)["dimensiones"]["alto"].asInt();
		int w = (*it)["dimensiones"]["ancho"].asInt();
		Sprite sprite = Sprite(x,y,w,h);
		sprite.set_background_color(255,130,15);
		(this->sprites).add(&sprite);
	}
}

SDL_Window* JsonLoader::obtener_ventana(){
	return this->ventana;
}

SpriteGroup JsonLoader::obtener_sprites(){
	return this->sprites;
}
