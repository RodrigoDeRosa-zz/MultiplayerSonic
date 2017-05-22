#include "JsonLoader.hpp"
#include <fstream>
#include "../Graficos/Renderer.hpp"
#include "../logger/current/Logger2.hpp"
#include "../Juego/Moneda.hpp"
#include "../Juego/Bonus.hpp"
#include "../Juego/Cangrejo.hpp"
#include "../Juego/Pez.hpp"
#include "../Juego/Pajaro.hpp"


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
#define MISSING_TEX_ERR "No se encontro la textura "
#define DEFAULT_PATH "json/ejemplo2.json"
#define DEFAULT_WIDTH 1200
#define DEFAULT_HEIGHT 640
#define DEFAULT_STAGE_WIDHT 3600
#define DEFAULT_STAGE_HEIGHT 640
#define DEFAULT_IMAGE "../Graficos/question.png"

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


JsonLoader::JsonLoader(char* ruta, char* rutaDefault){
	(colores["verde"]) = verde;
	(colores["rojo"]) = rojo;
	(colores["azul"]) = azul;
	(colores["amarillo"]) = amarillo;
	(colores["violeta"]) = violeta;

    this->setLogger();
	this->setJson(ruta, rutaDefault);
}

void JsonLoader::setJson(char* ruta, char* rutaDefault){
    //carga el .json
	ifstream in(ruta);
    Json::Value json;

    //no encuentra el archivo
	if(in.fail()){
		Logger::getInstance().log("No se encontro el archivo .json",BAJO);
		in.clear();
		in.open(rutaDefault);
	}

    //hay un error de sintaxis
	try{
		in >> json;
	}catch(const Json::RuntimeError& e){
		Logger::getInstance().log(string("Error de sintaxis en el archivo .json . Error: \n") + string(e.what()),BAJO);
		ifstream input(rutaDefault);
		input >> json;
	}
    this->json = json;
}

void JsonLoader::setLogger(){
    string level = getString((this->json)["log_lvl"],"[log_lvl]","bajo");
    if (level == "bajo") Logger::getInstance().setLogLevel(BAJO);
    else if (level == "medio") Logger::getInstance().setLogLevel(MEDIO);
    else if (level == "alto") Logger::getInstance().setLogLevel(ALTO);
    else Logger::getInstance().setLogLevel(BAJO);
}

Stage* JsonLoader::getStage(){
    Stage* stage = new Stage();

    this->validateValue((this->json)["escenario"],"[escenario]");

	stage->setDimensions(this->getPositiveInt((this->json)["escenario"]["dimensiones"]["ancho"],"[escenario][dimensiones][ancho]",DEFAULT_STAGE_WIDHT),
							this->getPositiveInt((this->json)["escenario"]["dimensiones"]["alto"],"[escenario][dimensiones][alto]",DEFAULT_STAGE_HEIGHT));

	if(this->validateValue((this->json)["escenario"]["capas"],"[escenario][capas]")){

		int i = 0;
		for(Json::Value::iterator it = (this->json)["escenario"]["capas"].begin(); it != (this->json)["escenario"]["capas"].end(); it++){
			if(i==2) break; //no hay mas de dos capas
			Layer* layer = this->getLayer((*it),i,stage->getWidth(),stage->getHeight());
            stage->addLayer(layer);
			i++;
		}
	}

    //SpriteGroup* activeSprites = this->getSprites((this->json));
    //stage->setSpriteGroup(activeSprites);
    //stage->addSpriteGroup("active", activeSprites);

    SpriteGroup* monedas = new SpriteGroup();
    Moneda* m1 = new Moneda(10, 300);
    m1->setBackgroundColor(200, 200, 0);
    m1->setIndexZ(99);
    monedas->add(m1);
    stage->addSpriteGroup("monedas", monedas);

    SpriteGroup* bonus = new SpriteGroup();
    Bonus* b1 = new Bonus(200, 300);
    b1->setBackgroundColor(80, 80, 80);
    b1->setIndexZ(99);
    bonus->add(b1);
    stage->addSpriteGroup("bonus", bonus);

    SpriteGroup* peces = new SpriteGroup();
    Pez* p1 = new Pez(300, 500);
    p1->setBackgroundColor(255, 0, 0);
    p1->setIndexZ(99);
    peces->add(p1);
    stage->addSpriteGroup("peces", peces);

    SpriteGroup* cangrejos = new SpriteGroup();
    Cangrejo* c1 = new Cangrejo(240, 400);
    c1->setBackgroundColor(180, 0, 180);
    c1->setIndexZ(99);
    cangrejos->add(c1);
    stage->addSpriteGroup("cagrejos", cangrejos);

    SpriteGroup* pajaros = new SpriteGroup();
    Pajaro* pj1 = new Pajaro(70, 150);
    pj1->setBackgroundColor(0, 0, 180);
    pj1->setIndexZ(99);
    pajaros->add(pj1);
    stage->addSpriteGroup("pajaros", pajaros);

    return stage;
}

Layer* JsonLoader::getLayer(Json::Value json, int layerNumber,int width, int height){
    Layer* layer = new Layer();
	layer->setTexPath(this->getString(json["ruta_imagen"],"[escenario][capas][ruta_imagen]"));
	layer->setDimensions( width, height);
	layer->loadImage();
	layer->setIndexZ(this->getPositiveInt(json["index_z"],"[escenario][capas][index_z]",layerNumber));
    return layer;
}

SpriteGroup* JsonLoader::getSprites(Json::Value json){

    map<string,Texture*> texturas = this->getTextures(json);

	SpriteGroup* activeSprites = new SpriteGroup();

	this->validateValue(json["escenario"]["entidades"],"[escenario][entidades]");

	int contadorEntidades = 0;

	for (Json::Value::iterator it = json["escenario"]["entidades"].begin(); it != json["escenario"]["entidades"].end(); it++) {

		string contador = SSTR( contadorEntidades );

        Sprite* sprite = this->getSprite((*it),contador,texturas);

        contadorEntidades++;

        if(!sprite) continue;

        activeSprites->add(sprite);
	}
	return activeSprites;
}

Sprite* JsonLoader::getSprite(Json::Value json, string contador, map<string,Texture*> texturas){

		int x = this->getPositiveInt(json["coordenada"]["x"],string("[escenario][entidades][") + contador + string("][coordenada][x]"),-1,true);
		int y = this->getPositiveInt(json["coordenada"]["y"],string("[escenario][entidades][") + contador + string("][coordenada][y]"),-1,true);

		vector<int> color = this->getColor(json["color"],string("[escenario][entidades][") + contador + string("][color]"));
		string imagen = getString(json["imagen"],string("[escenario][entidades][") + contador + string("][imagen]"));

		if(x<0 || y<0){
			Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
			return NULL;
		}

        //chequeo que el parametro "circulo" exista y sea bool
		bool binarioCirculo = validateValue(json["circulo"],string("[escenario][entidades][") + contador + string("][circulo]"))
			 && isBool(json["circulo"],string("[escenario][entidades][") + contador + string("][circulo]"));

		if(binarioCirculo && json["circulo"].asBool()){
			return this->getCirculo(json,contador,x,y,imagen,texturas,color);
		}
		else if(binarioCirculo){
			return this->getBloque(json,contador,x,y,imagen,texturas,color);
		}
        return NULL;
}

Bloque* JsonLoader::getBloque(Json::Value json, string contador, int x, int y, string imagen, map<string,Texture*> texturas, vector<int> color){
            int h = this->getPositiveInt(json["dimensiones"]["ancho"],string("[escenario][entidades][") + contador + string("][dimensiones][ancho]"),-1);
			int w = this->getPositiveInt(json["dimensiones"]["alto"],string("[escenario][entidades][") + contador + string("][dimensiones][alto]"),-1);
			if(h<0 || w<0){
				Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
				return NULL;
			}
			Bloque* bloque = new Bloque(x, y, h, w);
			bloque->setBackgroundColor(color[0],color[1],color[2]);
			bloque->setIndexZ(this->getPositiveInt(json["index_z"],string("[escenario][entidades][") + contador + string("][index_z]"), 0));
            if(imagen != string("")){
			    if(texturas.find(imagen) != texturas.end())
                    bloque->setTexture(texturas[imagen]);
                else{
		            Logger::getInstance().log(MISSING_TEX_ERR + imagen + string(" en la entidad ") + contador, MEDIO);
                    Texture* texture = new Texture();
                    texture->loadFromFile(DEFAULT_IMAGE);
                    bloque->setTexture(texture);
                }
            }
            return bloque;
}

Circulo* JsonLoader::getCirculo(Json::Value json, string contador, int x, int y, string imagen, map<string,Texture*> texturas, vector<int> color){
            int r = this->getPositiveInt(json["radio"],string("[escenario][entidades][") + contador + string("][radio]"),-1);
			if(r < 0){
				Logger::getInstance().log(JSONLOADER_SPRITE_NOCREAT_MSG,MEDIO);
				return NULL;
			}
			Circulo* circulo = new Circulo(x, y, r);
			circulo->setBackgroundColor(color[0],color[1],color[2]);
			circulo->setIndexZ(this->getPositiveInt(json["index_z"],string("[escenario][entidades][") + contador + string("][index_z]"), 0));
            //la ruta no es valida
			if(imagen == string("") || texturas.find(imagen) == texturas.end() || !(circulo->setTexture(imagen))){
                circulo->setTexture(DEFAULT_IMAGE);
		        Logger::getInstance().log(MISSING_TEX_ERR + imagen + string(" en la entidad ") + contador, MEDIO);
		    }
			return circulo;
}

map<string,Texture*> JsonLoader::getTextures(Json::Value json){

    this->validateValue(json["escenario"]["texturas"],"[escenario][texturas]");

    int contadorTexturas = 0;

	map<string,Texture*> texturas;

	for (Json::Value::iterator it = json["escenario"]["texturas"].begin(); it != json["escenario"]["texturas"].end(); it++) {

		string contador = SSTR( contadorTexturas );

        string ruta = getString((*it)["ruta"],string("[escenario][texturas][") + contador + string("][ruta]"));

        //la ruta no es una cadena
		if(ruta == string("")) {
			contadorTexturas++;
			continue;
		}

		Texture* texture = new Texture();

        //la ruta no es valida
		if(!(texture->loadFromFile(ruta)))
            texture->loadFromFile(DEFAULT_IMAGE);

		texturas[ruta] = texture;
	}
    return texturas;
}



void JsonLoader::setWindow(){
    int width = this->getPositiveInt((this->json)["ventana"]["dimensiones"]["ancho"], string("[ventana][dimensiones][ancho]"), DEFAULT_WIDTH);
    int height = this->getPositiveInt((this->json)["ventana"]["dimensiones"]["alto"], string("[ventana][dimensiones][alto]"), DEFAULT_HEIGHT);

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

Camara* JsonLoader::getCamara(Stage* stage){
	int velocidad = getPositiveInt((this->json)["vel_scroll"],"[vel_scroll]",1);
	Camara* camara_pantalla = new Camara(0,0,velocidad,Window::getInstance().getWidth(),Window::getInstance().getHeight(),(stage)->getWidth(), (stage)->getHeight() );
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

void JsonLoader::setGame(){
	this->setWindow();
	this->setRenderer();
}

string JsonLoader::getPort(){
	return this->getString((this->json)["port"],"port","9034");
}

string JsonLoader::getHostname(){
	return this->getString((this->json)["hostname"],"hostname","localhost");
}
