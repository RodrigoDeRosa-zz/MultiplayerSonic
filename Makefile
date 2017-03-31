#OBJS specifies which files to compile as part of the project
OBJS = Graficos/Window.cpp Graficos/Renderer.cpp Graficos/SDLHandler.cpp Graficos/Texture.cpp Graficos/Sprite.cpp Graficos/Layer.cpp Graficos/SpriteGroup.cpp Graficos/Apuntado.cpp Graficos/Circulo.cpp Graficos/Bloque.cpp Graficos/Stage.cpp Graficos/Camara.cpp JsonLoader.cpp jsoncpp.cpp main.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_gfx
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)
