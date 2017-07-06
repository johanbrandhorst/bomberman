// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Board.h
// Datum: 08/12/11

#ifndef BOARD_H
#define BOARD_H
#include "Class_SDL.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <map>
#include <vector>

class Object;
class Player;

class Board
{
 public:
  
  Board ();
  // Width, Height, Red, Green, Blue, Theme
  Board (int, int, int, int, int, int);
  ~Board ();
  
  // Medlemsfunktioner
  void clear();
  void set_tema(int);
  std::string convert(SDLKey) const;
  SDLKey deconvert(std::string);  

  // Scoreboard
  void add_points(std::string);
  void reset_points();
  void display_points(int);
  
  // Datamedlemmar
  std::map<int, Object*> indestructible_walls;
  std::map<int, Object*> dynamic_objects;
  std::map<int, Object*> power_ups;
  std::vector<Object*> players;
  std::vector<SDLKey> bindings;
  std::vector<std::string> bindings_text;
  int square_size;
  int kills;
  int kills_this_frame;
  bool humiliation;
  Class_SDL background;
  
  // Scoreboard
  std::map<std::string, int> score;
  
  // Bilder och ljud
  SDL_Surface* pic;
  std::vector<Mix_Chunk*> audio;
};

#endif
