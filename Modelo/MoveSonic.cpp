#include "MoveSonic.hpp"
#include "../message.hpp"
#include <stdio.h>

/*DIMENSIONES ESCENARIO*/
#define ANCHO_ESCENARIO 3600
#define ALTO_ESCENARIO 640
/*CONSTANTES*/
#define CONTROL_MOVIMIENTO 0.001
#define CONTROL_CAMINATA 1.0
#define CONTROL_SALTO 0.0001
#define FACTOR 12
#define FACTOR_FRENADO 1	//que tan rapido frena (deberia ser 10, pero para que se note que frena)

#define FACTOR_CHARGES	1
#define LIM_CHARGE 3
#define MAX_ROLL	100 	//numero a medir para limitar la cantidad de tiempo que rueda
/*MOVIMIENTOS*/
#define GRAVEDAD 0.5
#define SALTO -12.0
#define VELOCIDAD 0.35
#define RUN 0.7
#define VELOCIDAD_ROLL	3
/*FRAMES*/
#define WALKING_ANIMATION_FRAMES 14
#define RUNNING_ANIMATION_FRAMES 8
#define JUMPING_ANIMATION_FRAMES 5
#define QUIET_ANIMATION_FRAMES 7
//#define BALL_ANIMATION_FRAMES	6
//#define CROUCH_ANIMATION_FRAMES 2
#define BRAKE_ANIMATION_FRAMES	5

MoveSonic::MoveSonic(float x, float y){
    originX = x;
    originY = y;
    width = 117;
    tiempoX=0.0;
    tiempoY=0.0;
    tiempoSalto=0.0;
    frameRight = 0;
    frameLeft = 0;
    frameQuiet = 0;
    frameJumping = 0;
    frameActual = 0;
	charges = 0;
	noActionCounter = 0;
    //La direccion se setea en true cuando esta para la derecha.
    direccion = true;
    jumping = false;
	rolling = false;
	cont_roll=0;
}

void MoveSonic::setPosicionInicio(){
    tiempoX = 0.0;
    tiempoY = 0.0;
    tiempoSalto = 0.0;
    frameLeft=0;
    frameRight=0;
    frameJumping=0;
    jumping = false;
	rolling = false;
	charges = 0;
    if( frameQuiet / (FACTOR*QUIET_ANIMATION_FRAMES) >= QUIET_ANIMATION_FRAMES){
        frameQuiet=0;
    }
    //si esta apuntando para la derecha
    frameActual = (frameQuiet/(FACTOR*QUIET_ANIMATION_FRAMES));
    if(direccion){
        moveActual = IDLED;
    }
    else{
        moveActual = IDLEI;
    }
	//TODO si el noActionCounter no llego a cierto threshold que se freezee en la primer frame
    frameQuiet++;
	noActionCounter++;
}

void MoveSonic::cortarSalto() {

    jumping = false;
    frameJumping = 0.0;
    tiempoY = 0.0;
}

void MoveSonic::jump(float vel_x,float vel_y){
	noActionCounter=0;
	rolling = false; //MARTIN: molestara para que cuando cae siga rodando?
	charges=0;

    if( frameJumping / (4*JUMPING_ANIMATION_FRAMES) >= JUMPING_ANIMATION_FRAMES){
        frameJumping=0;
    }

    if(tiempoY == 0 && not jumping){
        tiempoY = SALTO;
        jumping = true;
    }

    float velH = 0;
    if(vel_x>0){
        jumpDerecha(&velH);
    }
    if(vel_x<0){
        jumpIzquierda(&velH);
    }

    frameActual = (frameJumping)/(4*JUMPING_ANIMATION_FRAMES);
    if(direccion){moveActual = JUMPD;}
    if(not direccion){moveActual = JUMPI;}

    originX += 3*(velH * tiempoSalto);
    originY += 2*(tiempoY * tiempoSalto);
    tiempoY += (GRAVEDAD * tiempoSalto);

    tiempoSalto += CONTROL_MOVIMIENTO;
    frameJumping ++;

    //Este chequeo se hace para que vuelva a empezar de 0 el salto.
    if(tiempoY >= (SALTO*-1) && jumping){
        tiempoSalto = 0.0;
        jumping = false;
        tiempoY = 0.0;
    }

}
void MoveSonic::roll(){
	if (jumping || false){//si esta saltando (u otros casos limitantes) ignorar
		return;
	}
	noActionCounter=0;
	jumping=0;
	if (!rolling){
		rolling=true;
		cont_roll=0;
	}
	cont_roll++;
	if (direccion){//rollDerecha
		moveActual=ROLLD;
		frameRight++;
		if (frameRight / (4*JUMPING_ANIMATION_FRAMES) >= JUMPING_ANIMATION_FRAMES){
			frameRight=0;
		}
		frameActual =  frameRight / (4*JUMPING_ANIMATION_FRAMES);
		
		if( originX + (width + VELOCIDAD_ROLL)> ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
		else {
			originX += VELOCIDAD_ROLL;
		}
	}
	else{//rollIzquierda
		moveActual=ROLLI;
		frameLeft++;
		if (frameLeft / (4*JUMPING_ANIMATION_FRAMES) >= JUMPING_ANIMATION_FRAMES){
			frameLeft=0;
		}
		frameActual =  frameLeft / (4*JUMPING_ANIMATION_FRAMES); 
		originX-= VELOCIDAD_ROLL;
	    if( originX < 0 ){originX = 0;}
	}

	if (cont_roll > MAX_ROLL){
		rolling=false;
		//this->setPosicionInicio();//resetea 
	}
}
void MoveSonic::jumpDerecha(float* velH){
    direccion = true;
    *velH = VELOCIDAD*5;
    if(tiempoX >= CONTROL_CAMINATA){
        *velH += RUN*2;
    }
    frameActual = ((frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    moveActual = JUMPD;
    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void MoveSonic::jumpIzquierda(float* velH){
    direccion = false;
    *velH = VELOCIDAD*(-5);
    if(tiempoX <= -CONTROL_CAMINATA){
        *velH -= RUN*2;
    }
    frameActual = ((frameJumping)/(4*JUMPING_ANIMATION_FRAMES));
    moveActual = JUMPI;
    if( originX < 0 ){originX = 0;}
}


void MoveSonic::moveRight(float vel_x){
	noActionCounter = 0;
	rolling = false; //MARTIN: molestara para que cuando cae siga rodando?
    //Si la VELOCIDAD era menor a 0, se movia para la izquierda.
    if(tiempoX <= 0.0){
		if(tiempoX <= -CONTROL_CAMINATA){//estaba corriendo y tiene que frenar
			//TODO

			tiempoX += CONTROL_MOVIMIENTO*FACTOR_FRENADO;
			if (tiempoX > 0) tiempoX=0; 		//por las dudas
			frenarIzquierda();
			frameLeft++;
    		if( originX < 0 ){originX = 0;}
			return;

		}
        jumping =false;
        direccion = true;
        frameLeft = 0;
        frameQuiet=0;
        tiempoX = 0.0;
    }
    //Actualizamos el control de movimiento
    tiempoX += CONTROL_MOVIMIENTO;

    if (tiempoX<CONTROL_CAMINATA){caminarDerecha();}
    else if(tiempoX>=CONTROL_CAMINATA){correrDerecha();}

    //Actualizamos el frame
    frameRight++;

    if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
}

void MoveSonic::moveLeft(float vel_x){
	noActionCounter=0;
	rolling = false; //MARTIN: molestara para que cuando cae siga rodando?
    //Si la VELOCIDAD era mayor a 0, se movia para la derecha
    if(tiempoX >= 0.0){
		if(tiempoX >= CONTROL_CAMINATA){//estaba corriendo y tiene que frenar
			//TODO

			tiempoX -= CONTROL_MOVIMIENTO*FACTOR_FRENADO;
			if (tiempoX < 0) tiempoX=0; 		//por las dudas
			frenarDerecha();
			frameRight++;
    		if( originX + width > ANCHO_ESCENARIO ){originX = ANCHO_ESCENARIO - width;}
			return;

		}
        jumping =false;
        direccion = false;
        frameRight =0;
        frameQuiet=0;
        tiempoX = 0.0;
    }
    //Actualizamos el control de movimiento.
    tiempoX -= CONTROL_MOVIMIENTO;

    if(tiempoX > -CONTROL_CAMINATA){caminarIzquierda();}
    else if(tiempoX <= -CONTROL_CAMINATA){correrIzquierda();}

    //actualizamos el frame
    frameLeft++;

    if( originX < 0 ){originX = 0;}
}

void MoveSonic::caminarDerecha(){
    if( frameRight / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameRight=0;
    }
    frameActual = (frameRight/WALKING_ANIMATION_FRAMES);
    moveActual = WALKD;
    originX += VELOCIDAD;
}

void MoveSonic::caminarIzquierda(){

    if( frameLeft / (WALKING_ANIMATION_FRAMES) >= WALKING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    frameActual = (frameLeft/WALKING_ANIMATION_FRAMES);
    moveActual = WALKI;
    originX -= VELOCIDAD;
}

void MoveSonic::correrDerecha(){
    if( frameRight / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameRight=0;
    }
    frameActual = (frameRight/RUNNING_ANIMATION_FRAMES);
    moveActual = RUND;
    float vel = VELOCIDAD + RUN;
    originX += vel;
}

void MoveSonic::correrIzquierda(){
    if( frameLeft / (RUNNING_ANIMATION_FRAMES) >= RUNNING_ANIMATION_FRAMES){
        frameLeft=0;
    }
    frameActual = (frameLeft/RUNNING_ANIMATION_FRAMES);
    moveActual = RUNI;
    float vel = (VELOCIDAD*-1) - RUN;
    originX += vel;
}

int MoveSonic::getFrame(){
    return frameActual;
}

move_type MoveSonic::getMovement(){
    return moveActual;
}

void MoveSonic::update(float new_x, float new_y){
    originX = new_x;
    originY = new_y;
}

bool MoveSonic::estaSaltando(){
    return jumping;
}

int MoveSonic::getX(){
    return originX;
}

int MoveSonic::getY(){
    return originY;
}

void MoveSonic::setX(float new_x){
    originX = new_x;
}

void MoveSonic::setY(float new_y){
    originY = new_y;
}


void MoveSonic::frenarDerecha(){
	bool cambiarFrameActual = true;
	if(tiempoX < CONTROL_CAMINATA){ //en la proxima ya sigue para el otro lado
									 //MARTIN: PUEDE QUE HAGA FALTA AJUSTAR A CAMINATA+THRESHOLD
    	frameActual=BRAKE_ANIMATION_FRAMES-1;
		cambiarFrameActual = false;
	}
    else if( frameRight / (BRAKE_ANIMATION_FRAMES) >= BRAKE_ANIMATION_FRAMES-1){
        frameActual=BRAKE_ANIMATION_FRAMES-2;//se queda en la anteultima
		cambiarFrameActual = false;
    }
    if (cambiarFrameActual){
		frameActual = (frameRight/BRAKE_ANIMATION_FRAMES);
	}
    moveActual = BRAKED;
	if (frameActual == BRAKE_ANIMATION_FRAMES-1){//la de darse vuelta, no avanza
			return;
	}
	float vel = (float) frameActual / -10.0;//NUMERO MAGICO PARA QUE DE 0,0.1,0.2 o 0.3
	vel+=VELOCIDAD;
	originX += vel;//originX += (VEL_CAMINAR - frameActual/10) ; esto es .35,.25,.15 y .05
}

void MoveSonic::frenarIzquierda(){
	bool cambiarFrameActual = true;
	if(tiempoX > -CONTROL_CAMINATA){ //en la proxima ya sigue para el otro lado
									 //MARTIN: PUEDE QUE HAGA FALTA AJUSTAR A -CAMINATA-THRESHOLD
    	frameActual=BRAKE_ANIMATION_FRAMES-1;
		cambiarFrameActual = false;
	}
    else if( frameLeft / (BRAKE_ANIMATION_FRAMES) >= BRAKE_ANIMATION_FRAMES-1){
        frameActual=BRAKE_ANIMATION_FRAMES-2;//se queda en la anteultima
		cambiarFrameActual = false;
    }
    if (cambiarFrameActual){
		frameActual = (frameLeft/BRAKE_ANIMATION_FRAMES);
	}
    moveActual = BRAKEI;
	if (frameActual == BRAKE_ANIMATION_FRAMES-1){//la de darse vuelta, no avanza
			return;
	}
	float vel = (float) frameActual / 10.0;//NUMERO MAGICO PARA QUE DE 0,0.1,0.2 o 0.3
	vel-=VELOCIDAD;
	originX += vel;//originX += (-VEL_CAMINAR + frameActual/10) ; esto es -.35,-.25,-.15 y -.05
}
/*
void MoveSonic::agacharseDerecha(){
    if( frameRight / (CROUCH_ANIMATION_FRAMES) >= CROUCH_ANIMATION_FRAMES){
        frameActual=CROUCH_ANIMATION_FRAMES-1;//se queda en la ultima, sino haria abs
    }
	else{
    frameActual = (frameRight/CROUCH_ANIMATION_FRAMES);
	}
    moveActual = CROUCHD;
}

void MoveSonic::agacharseIzquierda(){
    if( frameLeft / (CROUCH_ANIMATION_FRAMES) >= CROUCH_ANIMATION_FRAMES){
        frameActual=CROUCH_ANIMATION_FRAMES-1;//se queda en la ultima, sino haria abs
    }
	else {
    frameActual = (frameLeft/CROUCH_ANIMATION_FRAMES);
	}
    moveActual = CROUCHI;
}
*/
bool MoveSonic::estaRodando(){
	return rolling;
}

bool MoveSonic::estaMirandoADer(){
	return direccion;
}

//ESTA FUNCION SOLO DEBE SER LLAMADA SI LA VELOCIDAD NO ES 0 Y NO SE APRETARON TECLAS
void MoveSonic::decrementarVelocidad(){
	noActionCounter++;//esto solo se llama si no se realizo accion, y garantizo noActionCounter>0
	float X_viejo = originX;
	switch(moveActual){
		//TODO para cada caso mantener la animacion y lo que ello implique
	}
	float X_nuevo = originX;
	X_nuevo -= X_viejo;
	X_nuevo /= (float)noActionCounter;//no hay div0 error por el ++ de arriba
	originX += X_nuevo;//independiente de la direccion
	//TODO cambiar la velocidad para que en algun momento se detenga y llegue a setPosicionInicio()
}
