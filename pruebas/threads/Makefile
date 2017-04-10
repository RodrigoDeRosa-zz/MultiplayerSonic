#CC specifies which compiler we're using
CC= g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS= -w -g -std=c++11
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS= -pthread 
#This is the target that compiles our executable

help:
	man make

.PHONY: clean

clean:
	rm *.o 
$@:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $@.cpp -o $@  
