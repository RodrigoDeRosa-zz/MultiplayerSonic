/*
v2.0: Este tiene implementado adentro los mapas para .log(LOG_ERROR logerr)
v2.1: Logea a DEFAULT_OUTPUT_PATH en vez de stdout       
v2.2: Se agrega log(LOG_ERROR,string) para informacion adicional, si string es vacio asume log(LOG_ERROR)

TODO:	-agregar mas funciones sobrecargadas de log (aunque hace falta mas que esto?)
		
*/

#include <time.h>
#include <map>
#include "Logger2.hpp"
using namespace std;


//defines y qcyo
#define STR_FORMAT "%5s||%s\n"	//imprime asd  ||(mensaje)  !!!!!Usa 5 como espaciado
#define SEPARATOR "----------------------------------------\n----------------------------------------\n"
#define DEFAULT_OUTPUT_PATH  "tallerlog.txt"
#define INIT_MSG "Se inicia la ejecucion del programa con LogLv "
#define FIN_MSG	"Se termina la ejecucion del programa"
#define CAMBIO_LOGLV "Se cambia nivel de log a "
#define ADD_INFO_CONNECTOR  ".Info adicional: "


//singletons
Logger::Logger(){
		log_level = BAJO;
		output_file = fopen(DEFAULT_OUTPUT_PATH,"at");
		logProgStart();
		initMaps();
	}
Logger::~Logger(){
	logProgFinish();
	fclose(output_file);
}
Logger& Logger::getInstance(){
		static Logger instance;
		return instance;}

LOGLV Logger::getLogLevel(){
	return log_level;
}
void Logger::setLogLevel(LOGLV lv){
	log_level = (lv < LOGLV_TOTAL ? lv : ALTO);
	string s;	
	switch(lv){
		case BAJO:
			s="BAJO";break;
		case MEDIO:
			s="MEDIO";break;
		case ALTO:
			s="ALTO";break;
		default:
			s="ALTO por defecto (loglv ingresado invalido)";break;
	}
	log((string(CAMBIO_LOGLV))+s);
}

void Logger::log(string str){
	fprintf(output_file,STR_FORMAT,"N/E",str.c_str());
}


void Logger::log(LOG_ERROR logerr){

	log(logerr, string(""));
}

void Logger::log(LOG_ERROR logerr,string addinfo){
	LOGLV log_err_lv = log_error_prior[logerr];
	if (log_err_lv > log_level) return;
	string s;	
	switch(log_err_lv){
		case BAJO:
			s="BAJO";break;
		case MEDIO:
			s="MEDIO";break;
		case ALTO:
			s="ALTO";break;}
	string message = log_error_msg[logerr];
	if (addinfo.c_str() != string("")){		//si addinfo no es cadena vacia
		message = message + ADD_INFO_CONNECTOR + addinfo;
	}
	fprintf(output_file,STR_FORMAT,s.c_str(),message.c_str());
}

void Logger::logProgStart(){
	fprintf(output_file,SEPARATOR);
	string s;	
	switch(log_level){
		case BAJO:
			s="BAJO";break;
		case MEDIO:
			s="MEDIO";break;
		case ALTO:
			s="ALTO";break;}
	timestamp(output_file,string(INIT_MSG)+s);
}

void Logger::logProgFinish(){
	timestamp(output_file,FIN_MSG);
	fprintf(output_file,SEPARATOR);
}


/* FUNCION PARA APLICAR TIMESTAMP A MENSAJE
Ej de uso: 
	fprint_timestamp("inserte aqui mensaje")
Devuelve: 
	2017-03-18 01:39:18 inserte aqui mensaje
*/
void timestamp(FILE* outstream,string mensaje){
    char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = localtime (&now);

    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    fprintf (outstream,"%s %s\n", buff, mensaje.c_str());
}

/*
int main(){
	printf("PRUEBA INICIALIZACION+SET/GET LOGLV\n");
	Logger::getInstance();

	printf("Logger fue inicializado con log_level = %d\n",Logger::getInstance().getLogLevel());

	printf("A continuacion debe imprimir en formato que cambio a nivel medio\n");
	Logger::getInstance().setLogLevel(MEDIO);

	printf("Logger ahora tiene log_level = %d\n",Logger::getInstance().getLogLevel());

	printf("\nPRUEBA .log(string) con hola\n");
	Logger::getInstance().log("hola");	

	printf("\nPRUEBA .log(LOG_ERROR) con JSON_NOT_FOUND\n");
	Logger::getInstance().log(JSON_NOT_FOUND);

	printf("\nPRUEBA .log(LOG_ERROR,string) con JSON_NOT_FOUND y \"asd\"\n");
	Logger::getInstance().log(JSON_NOT_FOUND,string("asd"));

	for (int i = 0; i<0xffffffff; i++);//espera un poquito antes de irse

	return 0;
}
*/
//Acá va la lista de errores (a completar)
void Logger::initMaps(){
	log_error_msg[JSON_NOT_FOUND]="Archivo JSON no encontrado";
	log_error_prior[JSON_NOT_FOUND]=BAJO;

	log_error_msg[JSON_SYNTAX]="Archivo JSON corrupto: sintaxis erronea";
	log_error_prior[JSON_SYNTAX]=BAJO;
}

