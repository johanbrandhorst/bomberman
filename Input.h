// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Input.h
// Datum: 08/12/11

#ifndef INPUT_H
#define INPUT_H
#include "SDL/SDL.h"

class Input
{
 public:
  Input ();
  ~Input ();

  // Medlemsfunktioner
  void readInput ();
  bool* getInput ();
  bool* getPressed ();
  bool windowClosed ();

  // Datamedlemmar
  SDL_Event event;
  bool keysHeld[323];
  bool keysPressed[323];
  bool windowClose;
};

#endif
