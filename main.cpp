#include "Graficos/Window.hpp"
#include "Graficos/Renderer.hpp"
#include "Graficos/SDLHandler.hpp"
#include "Graficos/Stage.hpp"
#include "Graficos/Texture.hpp"
#include "Graficos/Camara.hpp"
#include "Juego/Juego.hpp"
#include "json/JsonLoader.hpp"
#include "Juego/SegaFactory.hpp"
#include "Juego/Sonic.hpp"
#include "Logger2.hpp"
#include <SDL2/SDL.h>


int main(int argc, char** argv){
	Logger::getInstance();	//se inicializa el logger .
    SDLHandler::getInstance().init();

    JsonLoader* json = new JsonLoader("json/ejemplo.json");

    Stage* stage = json->getStage();

		Juego* juego = new Juego();
		juego->setStage(stage);
		Camara* camara_pantalla = json->getCamara();
		juego->setCamara(camara_pantalla);
		Jugadores* jugs = new Jugadores();
		juego->setJugadores(jugs);
		//juego->addJugador("facu","Sonic");

		SegaFactory* factory = new SegaFactory();
		Sonic* sonic = factory -> getSonic("0");

    bool running = true;
    SDL_Event e;

		float velX = 0.0;
		float velY = 0.0;

		/*Estas son variables que se le pasan a los personajes,
		pero dentro de cada personaje sabe con que velocidad se tiene
		que mover. esta velocidad no es con la que se va a mover el
		jugador, sirve para saber para que lado se esta moviendo.

		---- velX > 0 implica que se mueve para la derecha.
		---- velY > 0 implica que salto.
		*/

		float velocidadHorizontal = 0.35;
		float velocidadVertical = -12.0;
    while(running){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                running = false;
                break;}

						/*ESTO ES SUPER CABEZA PERO LO TIENE QUE MANEJAR EL
						SERVER, ES UN EJEMPLO DE COMO LO TIENE QUE HACER*/

            //sonic->setEventMovimiento(e);
						if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
							switch( e.key.keysym.sym ){
								case SDLK_SPACE: velY += velocidadVertical; break;
								case SDLK_LEFT: velX -= velocidadHorizontal; break;
								case SDLK_RIGHT: velX += velocidadHorizontal; break;
							}
						}
						else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
							switch( e.key.keysym.sym ){
								case SDLK_SPACE: velY -= velocidadVertical; break;
								case SDLK_LEFT: velX += velocidadHorizontal; break;
								case SDLK_RIGHT: velX -= velocidadHorizontal; break;
							}
						}
        }

				//printf("Velocidad sin dividir:%f \n",velX);

				//se le envia un string que dice que movimiento va a realizar

				sonic->update(velX,velY);
        //camara_pantalla->moveApuntado();
				//calcular mov camara con todos los personajes
				//camara_pantalla->moveCamara();

        //setea el color de fondo de blanco
        Renderer::getInstance().setDrawColor(255, 255, 255, 1);

        Renderer::getInstance().clear();
				juego->render();
				sonic->render(camara_pantalla);
        //camara_pantalla->render();
        Renderer::getInstance().draw();
    }
    delete stage;
    SDLHandler::getInstance().close();

    return 0;
}
