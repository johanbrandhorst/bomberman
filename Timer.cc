// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Timer.cc
// Datum: 08/12/11

#include "SDL/SDL.h"
#include "Timer.h"
using namespace std;

Timer::Timer ()
{
  // Konstruktor
  startTicks = 0;
  pausedTicks = 0;
  paused = false;
  started = false;
}

void
Timer::start ()
{
  // Starta timern
  started = true;

  // Av-pausa timern
  paused = false;

  // Sätt ticks till nuvarande klock-ticks
  startTicks = SDL_GetTicks ();
}

void
Timer::stop ()
{
  // Stanna timern
  started = false;

  // Av-pausa timern
  paused = false;
}

int
Timer::get_ticks ()
{
  // Om timern är påslagen
  if (started == true)
    // Om timern är pausad
    if (paused == true)
      // Returnera antalet ticks när timern pausades
      return pausedTicks;
    else
      // Om timern inte är pausad, returnera nuvarande ticks
      // minus start ticks.
      return SDL_GetTicks () - startTicks;

  // Om timern inte är påslagen
  return 0;
}

void
Timer::pause ()
{
  // Om timern är påslagen och inte redan pausad
  if (started && !paused)
  {
    // Pausa timern och räkna ut vid vilken tick den pausades
    paused = true;
    pausedTicks = SDL_GetTicks () - startTicks;
  }
}

void
Timer::unpause ()
{
  // Om timern är pausad
  if (paused)
  {
    // Av-pausa timern, ta bort antalet ticks som gått sedan det pausades
    // och nollställ pausedTicks.
    paused = false;
    startTicks = SDL_GetTicks () - pausedTicks;
    pausedTicks = 0;
  }
}

bool
Timer::is_started ()
{
  return started;
}

bool
Timer::is_paused ()
{
  return paused;
}
