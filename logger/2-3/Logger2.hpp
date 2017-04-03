/*
v2.0: Este tiene implementado adentro los mapas para .log(LOG_ERROR logerr)
v2.1: Logea a DEFAULT_OUTPUT_PATH en vez de stdout       
v2.3: Se agrega .log(const char*) wrapper de .log(string) para ahorrar sintaxis, se prueba de flushear

TODO:	-agregar mas funciones sobrecargadas de log (aunque hace falta mas que esto?)
		
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <exception>

using namespace std; 

//utility
enum LOGLV {BAJO,MEDIO,ALTO,LOGLV_TOTAL};	

void timestamp(FILE* outstream,string mensaje);

enum LOG_ERROR {JSON_NOT_FOUND,JSON_SYNTAX,LOG_ERROR_TOTAL}; //dejar TOTAL siempre al final

//end:utility

//CLASE LOGGER
class Logger {
	Logger();
	LOGLV	log_level;
	//funciones de inicio y fin del programa
	void logProgStart();
	void logProgFinish();

public:
	static Logger& getInstance();
	void setLogLevel(LOGLV lv);
	LOGLV getLogLevel();
	//inicio y fin de funciones de logging con lo que reciben
	void log(string str);	//string(generica)
	void log(const char* str);	//string de c
	void log(LOG_ERROR logerr);	//por código de error
	void log(LOG_ERROR logerr,string addinfo); //codigo de error+info adicional
	//void log(exception e);	//excepcion (hara falta?)


private:
	FILE* output_file;
	map<LOG_ERROR,string> log_error_msg;	//mensaje correspondiente a cada error
	map<LOG_ERROR,LOGLV> log_error_prior;	//nivel de detalle correspondiente a cada error
	~Logger();	
	void initMaps();
};
//end:CLASE LOGGER
