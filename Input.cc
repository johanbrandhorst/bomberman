// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Input.cc
// Datum: 08/12/11

#include "Input.h"

using namespace std;

Input::Input ()
{
  // Konstruktor, sätt alla input till false och
  // windowClose false.

  windowClose = false;
  for (int i = 0; i < 323; i++)
    {
      keysHeld[i] = false;
      keysPressed[i] = false;
    }
}

Input::~Input () {
  // Dummy-destruktor
}

void
Input::readInput ()
{
  // Resetta vilka knappar som tryckts sedan senaste framen
  for (int i = 0; i < 323; i++)
    keysPressed[i] = false;

  // Hämta events
  if (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
	{
	  exit(EXIT_SUCCESS);
	}

  // Om en knapp tryckts ned
  if (event.type == SDL_KEYDOWN)
	{
	  // Sätt knappens värde till true
	  keysHeld[event.key.keysym.sym] = true;
	}

      // Om en knapp sl�ppts upp
      if (event.type == SDL_KEYUP)
	{
	  // Sätt knappens värde till false
	  keysHeld[event.key.keysym.sym] = false;
	  // Sätt knappen till tryckt = true
	  keysPressed[event.key.keysym.sym] = true;
	}
    }
}

bool*
Input::getInput ()
{
  return keysHeld;
}

bool*
Input::getPressed ()
{
  return keysPressed;
}

bool
Input::windowClosed ()
{
  return windowClose;
}
