# NOMBRE DEL EJECUTABLE DEL TP
EXEC = prueba
CC = g++
CFLAGS = -pthread -g -Wno-write-strings
BIN = $(filter-out $(EXEC).cpp, $(wildcard *.cpp))
BINFILES = $(BIN:.cpp=.o)

all: main

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

main: $(BINFILES)  $(EXEC).cpp
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).cpp -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

.PHONY: clean main
