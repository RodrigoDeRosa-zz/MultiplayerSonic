#Source files
SRCS =  $(wildcard ../../../logger/current/Logger2.cpp \
../../../Modelo/*.cpp \
../../../Modelo/Entidades/*.cpp \
../../../Modelo/Entidades/Piedras/*.cpp \
../../../Modelo/Estado/*.cpp \
../../../json/jsoncpp.cpp \
../../../Control/*.cpp \
*.cpp)
OBJS = $(SRCS:.cpp=.o)
CC = g++
#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CPPFLAGS = -w -g -std=c++0x
#LINKER_FLAGS specifies the libraries we're linking against
LDFLAGS = -I ./logger/current -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

all: main

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

main: $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -o mainServer
run:
	./mainServer asd

clean:
	rm -f $(wildcard *.o) $(OBJS) mainServer
