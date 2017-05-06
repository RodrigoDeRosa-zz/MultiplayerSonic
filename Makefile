#OBJS specifies which files to compile as part of the project
OBJS = logger/current/Logger2.cpp Graficos/Window.cpp Graficos/Renderer.cpp Modelo/Model.cpp Modelo/Player.cpp Control/*.cpp Graficos/SDLHandler.cpp Graficos/Texture.cpp Graficos/Sprite.cpp Graficos/Layer.cpp Graficos/SpriteGroup.cpp Graficos/Apuntado.cpp Graficos/Bloque.cpp Graficos/Circulo.cpp Juego/MovingBloque.cpp Juego/MovingSonic.cpp Graficos/Stage.cpp Graficos/Camara.cpp Juego/Jugadores.cpp Juego/Juego.cpp Juego/Jugador.cpp Juego/Personaje.cpp Juego/Sonic.cpp Juego/SegaFactory.cpp json/JsonLoader.cpp json/jsoncpp.cpp Juego/ClipGroup.cpp Juego/Clip.cpp main.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -I ./logger/current -lSDL2 -lSDL2_image -opencv2 -lopencv_highgui -lopencv_imgproc -lopencv_core
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

nolink : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -c $(LINKER_FLAGS)
run:
	./$(OBJ_NAME)

.PHONY: clean

clean:
	rm *.o
