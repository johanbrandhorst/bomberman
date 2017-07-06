// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Timer.h
// Datum: 08/12/11

#ifndef TIMER_H
#define TIMER_H

class Timer
{
 public:
  Timer ();

  // Medlemsfunktioner
  void start ();
  void stop ();
  void pause ();
  void unpause ();

  // Returnera ticks
  int get_ticks ();

  // Statusfunktioner
  bool is_started ();
  bool is_paused ();

 private:
  int startTicks;
  int pausedTicks;

  bool paused;
  bool started;
};

#endif
