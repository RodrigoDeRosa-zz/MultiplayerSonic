#include "SegaFactory.hpp"

#define SONIC "Sonic"
#define MAX_SPRITES 7
using namespace std;

SegaFactory::SegaFactory(){
    Texture* tex1 = new Texture();
    tex1->loadFromFile("../../../Graficos/sonicSprites.png");
    texturas.push_back(tex1);

    Texture* tex2 = new Texture();
    tex2->loadFromFile("../../../Graficos/sonicSpritesVioleta.png");
    texturas.push_back(tex2);

    Texture* tex3 = new Texture();
    tex3->loadFromFile("../../../Graficos/sonicSpritesRojo.png");
    texturas.push_back(tex3);

    Texture* tex4 = new Texture();
    tex4->loadFromFile("../../../Graficos/sonicSpritesCian.png");
    texturas.push_back(tex4);

    Texture* tex5 = new Texture();
    tex5->loadFromFile("../../../Graficos/sonicSpritesRosa.png");
    texturas.push_back(tex5);

    Texture* tex6 = new Texture();
    tex6->loadFromFile("../../../Graficos/sonicSpritesDorado.png");
    texturas.push_back(tex6);

    Texture* tex7 = new Texture();
    tex7->loadFromFile("../../../Graficos/sonicSpritesNaranja.png");
    texturas.push_back(tex7);

}

Sonic* SegaFactory::getSonic(string nomJugador){
      Sonic* sonic = new Sonic(nomJugador);
      //todos los sprites con sus texturas se tendrian que crear en el json loader
      /*creacion de el bloque */
      MovingSonic* bloque = new MovingSonic(100, 300, 1500, 3000);
      int idJugador = atoi(nomJugador.c_str());
      if(idJugador >= MAX_SPRITES){
          //llamada al log, "nombre del jugador invalido"
          idJugador = 0;
      }
      bloque->setTexture(texturas[idJugador]);

      sonic->setMovingBloque(bloque);

      initClips(bloque);

      return sonic;
}

void SegaFactory::initClips(MovingSonic* sonic){

  sonic->setClip("quietoDer");
  sonic->setRectangulo("quietoDer",0,1452,92,121);
  sonic->setRectangulo("quietoDer",92,1452,97,121);
  sonic->setRectangulo("quietoDer",189,1452,97,121);
  sonic->setRectangulo("quietoDer",286,1452,91,121);
  sonic->setRectangulo("quietoDer",377,1452,95,121);
  sonic->setRectangulo("quietoDer",472,1452,95,121);
  sonic->setRectangulo("quietoDer",567,1452,95,121);

  sonic->setClip("quietoIzq");
  sonic->setRectangulo("quietoIzq",0,1573,92,121);
  sonic->setRectangulo("quietoIzq",94,1573,97,121);
  sonic->setRectangulo("quietoIzq",191,1573,97,121);
  sonic->setRectangulo("quietoIzq",288,1573,91,121);
  sonic->setRectangulo("quietoIzq",379,1573,95,121);
  sonic->setRectangulo("quietoIzq",474,1573,95,121);
  sonic->setRectangulo("quietoIzq",569,1573,95,121);

  sonic->setClip("caminarDer");
  sonic->setRectangulo("caminarDer",0,726,111,121);
  sonic->setRectangulo("caminarDer",111,726,112,121);
  sonic->setRectangulo("caminarDer",223,726,115,121);
  sonic->setRectangulo("caminarDer",338,726,100,121);
  sonic->setRectangulo("caminarDer",438,726,78,121);
  sonic->setRectangulo("caminarDer",516,726,80,121);
  sonic->setRectangulo("caminarDer",596,726,95,121);
  sonic->setRectangulo("caminarDer",691,726,117,121);
  sonic->setRectangulo("caminarDer",808,726,117,121);
  sonic->setRectangulo("caminarDer",925,726,95,121);
  sonic->setRectangulo("caminarDer",1020,726,78,121);
  sonic->setRectangulo("caminarDer",1098,726,79,121);
  sonic->setRectangulo("caminarDer",1177,726,85,121);
  sonic->setRectangulo("caminarDer",1262,726,90,121);

  sonic->setClip("caminarIzq");
  sonic->setRectangulo("caminarIzq",0,847,111,121);
  sonic->setRectangulo("caminarIzq",111,847,112,121);
  sonic->setRectangulo("caminarIzq",223,847,115,121);
  sonic->setRectangulo("caminarIzq",338,847,100,121);
  sonic->setRectangulo("caminarIzq",438,847,78,121);
  sonic->setRectangulo("caminarIzq",516,847,80,121);
  sonic->setRectangulo("caminarIzq",596,847,95,121);
  sonic->setRectangulo("caminarIzq",691,847,117,121);
  sonic->setRectangulo("caminarIzq",808,847,117,121);
  sonic->setRectangulo("caminarIzq",925,847,95,121);
  sonic->setRectangulo("caminarIzq",1020,847,78,121);
  sonic->setRectangulo("caminarIzq",1098,847,79,121);
  sonic->setRectangulo("caminarIzq",1177,847,85,121);
  sonic->setRectangulo("caminarIzq",1262,847,90,121);

  sonic->setClip("correrDer");
  sonic->setRectangulo("correrDer",0,968,96,121);
  sonic->setRectangulo("correrDer",96,968,96,121);
  sonic->setRectangulo("correrDer",192,968,98,121);
  sonic->setRectangulo("correrDer",290,968,94,121);
  sonic->setRectangulo("correrDer",384,968,96,121);
  sonic->setRectangulo("correrDer",480,968,88,121);
  sonic->setRectangulo("correrDer",568,968,98,121);
  sonic->setRectangulo("correrDer",666,968,94,121);

  sonic->setClip("correrIzq");
  sonic->setRectangulo("correrIzq",0,1089,96,121);
  sonic->setRectangulo("correrIzq",96,1089,96,121);
  sonic->setRectangulo("correrIzq",192,1089,98,121);
  sonic->setRectangulo("correrIzq",290,1089,94,121);
  sonic->setRectangulo("correrIzq",384,1089,96,121);
  sonic->setRectangulo("correrIzq",480,1089,88,121);
  sonic->setRectangulo("correrIzq",568,1089,98,121);
  sonic->setRectangulo("correrIzq",666,1089,94,121);

  sonic->setClip("saltarDer");
  sonic->setRectangulo("saltarDer",0,1694,94,121);
  sonic->setRectangulo("saltarDer",94,1694,91,121);
  sonic->setRectangulo("saltarDer",185,1694,91,121);
  sonic->setRectangulo("saltarDer",276,1694,91,121);
  sonic->setRectangulo("saltarDer",367,1694,91,121);

  sonic->setClip("saltarIzq");
  sonic->setRectangulo("saltarIzq",0,1815,94,121);
  sonic->setRectangulo("saltarIzq",94,1815,91,121);
  sonic->setRectangulo("saltarIzq",185,1815,91,121);
  sonic->setRectangulo("saltarIzq",276,1815,91,121);
  sonic->setRectangulo("saltarIzq",367,1815,91,121);

  sonic->setClip("esperandoDer");
  sonic->setRectangulo("esperandoDer",0,1452,92,121);

  sonic->setClip("esperandoIzq");
  sonic->setRectangulo("esperandoIzq",0,1573,92,121);

  sonic->setClip("frenoDer");
  sonic->setRectangulo("frenoDer",0,1210,108,121);
  sonic->setRectangulo("frenoDer",108,1210,105,121);
  sonic->setRectangulo("frenoDer",213,1210,95,121);
  sonic->setRectangulo("frenoDer",308,1210,92,121);

  sonic->setClip("frenoIzq");
  sonic->setRectangulo("frenoIzq",0,1331,108,121);
  sonic->setRectangulo("frenoIzq",108,1331,105,121);
  sonic->setRectangulo("frenoIzq",213,1331,95,121);
  sonic->setRectangulo("frenoIzq",308,1331,92,121);

  sonic->setClip("bolaDer");
  sonic->setRectangulo("bolaDer",0,484,90,121);
  sonic->setRectangulo("bolaDer",90,484,85,121);
  sonic->setRectangulo("bolaDer",175,484,86,121);
  sonic->setRectangulo("bolaDer",261,484,86,121);
  sonic->setRectangulo("bolaDer",347,484,85,121);
  sonic->setRectangulo("bolaDer",432,484,87,121);

  sonic->setClip("bolaIzq");
  sonic->setRectangulo("bolaIzq",0,605,90,121);
  sonic->setRectangulo("bolaIzq",90,605,85,121);
  sonic->setRectangulo("bolaIzq",175,605,86,121);
  sonic->setRectangulo("bolaIzq",261,605,86,121);
  sonic->setRectangulo("bolaIzq",347,605,85,121);
  sonic->setRectangulo("bolaIzq",432,605,87,121);

  sonic->setClip("damageDer");
  sonic->setRectangulo("damageDer",0,1210,108,121);
  sonic->setRectangulo("damageDer",108,1210,105,121);
  sonic->setRectangulo("damageDer",213,1210,95,121);

  sonic->setClip("damageIzq");
  sonic->setRectangulo("damageIzq",0,1331,108,121);
  sonic->setRectangulo("damageIzq",108,1331,105,121);
  sonic->setRectangulo("damageIzq",213,1331,95,121);

  sonic->setClip("agachadoDer");
  sonic->setRectangulo("agachadoDer",0,0,72,121);
  sonic->setRectangulo("agachadoDer",72,0,93,121);

  sonic->setClip("agachadoIzq");
  sonic->setRectangulo("agachadoIzq",0,121,72,121);
  sonic->setRectangulo("agachadoIzq",72,121,93,121);
}
