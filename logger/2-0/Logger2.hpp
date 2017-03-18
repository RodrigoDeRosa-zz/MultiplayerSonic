#include <stdio.h>
#include <iostream>
#include <string>
#include <exception>

using namespace std; 

/*			PARA AGREGAR UN CODIGO DE ERROR NUEVO
Recordar que para agregar un LOG_ERROR nuevo hay que agregarlo a la lista de enum LOG_ERROR aca 
y luego se especifica mensaje y prioridad en el cpp
*/


//utility
enum LOGLV {BAJO,MEDIO,ALTO,LOGLV_TOTAL};	

void timestamp(FILE* outstream,string mensaje);

enum LOG_ERROR {JSON_NOT_FOUND,JSON_SYNTAX,LOG_ERROR_TOTAL}; //dejar TOTAL siempre al final

//end:utility

//CLASE LOGGER
class Logger {
	Logger();
	LOGLV	log_level;

public:
	static Logger& getInstance();
	void setLogLevel(LOGLV lv);
	LOGLV getLogLevel();
	//funciones de inicio y fin del programa
	void logProgStart();
	void logProgFinish();
	//inicio y fin de funciones de logging con lo que reciben
	void log(string str);	//string(generica)
	void log(LOG_ERROR logerr);	//por código de error
	//void log(exception e);	//excepcion (hara falta?)


private:
	FILE* output_file;
	map<LOG_ERROR,string> log_error_msg;	//mensaje correspondiente a cada error
	map<LOG_ERROR,LOGLV> log_error_prior;	//nivel de detalle correspondiente a cada error
	void initMaps();
};
//end:CLASE LOGGER
