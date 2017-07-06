// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Menu.h
// Datum: 08/12/11

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Object.h"
#include "Input.h"

class Menu
{
 public:
  Menu ();
  // Kompilatorgenererad destruktor

  // Medlemsfunktioner
  void create_board (const char*);

  void set_key(int);
  void draw_keys(std::string, int, int);

  void draw_settings(std::string, std::string, int);
  std::string int_to_string(int);

  void start_game ();
  void start_menu();
  void finished();
  void paused();

  void update (Input&, int);
  bool load_settings (std::string);
  bool save_settings ();

  //Datamedlemmar
  int lives;
  int number_of_players;
  int bana;
  int tema;
  int fps;
  Board* current_board;
  SDL_Surface* bg;
  Class_SDL startup;
  std::vector<std::string> banor;
  bool game_finished;
  bool game_paused;

};

#endif
