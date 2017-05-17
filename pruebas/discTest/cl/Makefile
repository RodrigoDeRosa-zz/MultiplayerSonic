#OBJS specifies which files to compile as part of the project
OBJS = ../../../logger/current/Logger2.cpp ../../../Graficos/*.cpp ../../../Juego/*.cpp ../../../json/*.cpp *.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -I ./logger/current -lSDL2 -lSDL2_image -opencv2 -lopencv_highgui -lopencv_imgproc -lopencv_core -lpthread
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = mainClient
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
