// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Class_SDL.h
// Datum: 08/12/11

#ifndef CLASS_SDL_H
#define CLASS_SDL_H
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

class Class_SDL
{
 public:

  Class_SDL ();
  Class_SDL (int, int, int, int, int);
  ~Class_SDL ();

  // Medlemsfunktioner
  void Init ();
  void start ();
  void end ();

  // Musikfunktioner
  Mix_Chunk* load_audio(const char*);
  void play(Mix_Chunk*, int);
  void free_audio(Mix_Chunk*);

  //Bildfunktioner
  SDL_Surface* load (const char*);
  void free (SDL_Surface*);
  void drawSprite (SDL_Surface*, int, int, int, int, int, int);
  void setBGColor (int, int, int);

  // Text
  void drawText (std::string, int, int, int, int, int, int);

  // Datamedlemmar
  SDL_Surface* screen;
  Mix_Chunk* audio;

  int width;
  int height;
  int BGred;
  int BGgreen;
  int BGblue;
};

#endif

