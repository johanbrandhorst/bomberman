#
# Compiles Bomberman with g++
#
CCC = g++
CCFLAGS = -g -std=c++98 -pedantic -Wall -Wextra $(shell sdl-config --cflags)
SDLFLAGS = $(shell sdl-config --libs) -lSDL_image -lSDL_ttf -lSDL_mixer

Bomberman :  main.o Object.o Menu.o Input.o Class_SDL.o Board.o Timer.o
	$(CCC) $(CCFLAGS) $(SDLFLAGS) -o Bomberman main.o Object.o Menu.o Input.o Class_SDL.o Board.o Timer.o

main.o : main.cc
	$(CCC) $(CCFLAGS) -c main.cc

Object.o : Object.cc Object.h
	$(CCC) $(CCFLAGS) -c Object.cc

Menu.o : Menu.cc Menu.h
	$(CCC) $(CCFLAGS) -c Menu.cc

Input.o : Input.cc Input.h
	$(CCC) $(CCFLAGS) -c Input.cc

Class_SDL.o : Class_SDL.cc Class_SDL.h
	$(CCC) $(CCFLAGS) -c Class_SDL.cc

Board.o : Board.cc Board.h
	$(CCC) $(CCFLAGS) -c Board.cc

Timer.o : Timer.cc Timer.h
	$(CCC) $(CCFLAGS) -c Timer.cc

# Städa arbetsmappen

clean :
	@ \rm -f *.o
