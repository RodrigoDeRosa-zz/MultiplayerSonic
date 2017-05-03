#OBJS specifies which files to compile as part of the project
OBJS = *.cpp
#CC specifies which compiler we're using
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = prueba
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

nolink : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -c 
run:
	./$(OBJ_NAME)

.PHONY: clean

clean:
	rm *.o
