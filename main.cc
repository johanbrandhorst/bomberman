// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// main.cc
// Datum: 08/12/11

#include "Class_SDL.h"
#include "Input.h"
#include "Menu.h"
#include "Board.h"
#include "Timer.h"
#include <string>
#include <iostream>
using namespace std;

int
main (int argc, char** argv)
{
  // Input-objekt för att hantera knapptryckningar i spelloopen
  Input input;

  // Menu-objekt som används i startmenyn och spelloopen
  Menu game;

  // Timer-objekt som används för att hålla reda på hur många
  // ticks som passerat i varje frame och vänta så att max fps inte
  // överstiger game.fps.
  Timer fps;

  // Bool som används för att stoppa spelloopen
  bool gameIsRunning = true;
  // Bool som används i spelloopen och menyn
  game.game_finished = false;
  game.game_paused = false;

  // Hur många frames spelet ska v�nta tills det avslutas
  // när det bara finns en spelare kvar
  int finished_counter = 3;
  // Animations-hjälpare, inkrementeras i spelloopen
  int animation = 0;

  // Starta start-menyn
  game.start_menu ();

  // Starta spelet
  game.start_game ();

  while (gameIsRunning)
    {
      // Inkrementeras med 1 om animation < 29 annars sätts till 0 (Modulo 30).
      animation = (animation + 1) % 30;

      // Starta fps-timern.
      fps.start ();

      // Om spelet inte är slut men räknaren är 0, resetta räknaren.
      if (!finished_counter && !game.game_finished)
	      finished_counter = 3;

      // Om det finns en eller färre spelare kvar och finished counter
      // är > 1, räkna ner finished counter och sätt game_finished.
      if (game.current_board->players.size () <= 1 && finished_counter)
      {
        finished_counter--;
        game.game_finished = true;
      }

      // Om finished_counter är 0 och spelet är slut
      if (!finished_counter && game.game_finished)
      {
        // ö�r finished-funktionen
        game.finished ();

        // Nollställ alla knapptryck
        for (int i = 0; i < 323; i++)
          {
            input.keysHeld[i] = false;
            input.keysPressed[i] = false;
          }
      }
      else if (game.game_paused)
	      game.paused ();
      // Om spelet inte är slut eller pausat
      else
      {
        // Läs input
        input.readInput ();

        bool* keysPressed = input.getPressed ();

        // Om escape har tryckts, öppna startmenyn
        if(keysPressed[SDLK_ESCAPE])
          game.game_paused = true;
        else
          // Uppdatera spelplanen
          game.update (input, animation);
      }

      // Spela upp ljud

      // Om spelaren är den första som dör och bara en spelare
      // dör den framen, spela audio[1] (firstblood) och nollställ
      // kills_this_frame.
      if (game.current_board->kills == 1 &&
	      game.current_board->kills_this_frame == 1 &&
	      !game.current_board->humiliation)
      {
        game.current_board->background.play (game.current_board->audio[1], 0);
        game.current_board->kills_this_frame = 0;
      }

      // Om mer än en spelare dör den framen, spela audio[5]
      // (multikill) och nollställ kills_this_frame.
      else if (game.current_board->kills_this_frame > 1)
      {
        game.current_board->background.play (game.current_board->audio[5], 0);
        game.current_board->kills_this_frame = 0;
      }

      // Om en spelare dör, spela audio[2] (headshot)
      else if (game.current_board->kills_this_frame == 1 &&
	       !game.current_board->humiliation)
      {
        game.current_board->background.play (game.current_board->audio[2], 0);
        game.current_board->kills_this_frame = 0;
      }

      // Om humiliation inträffat, spela ljudet och sätt humiliation false.
      else if (game.current_board->humiliation)
      {
        game.current_board->background.play (game.current_board->audio[4], 0);
        game.current_board->humiliation = false;
        game.current_board->kills_this_frame = 0;
      }

      // Om antalet timer-ticks är
      // mindre än 1000ms/FPS vänta så många ticks som är kvar.
      if (fps.get_ticks () < 1000 / game.fps)
        SDL_Delay (1000 / game.fps - fps.get_ticks ());

      // SDL-Flippa spelplanen
      game.current_board->background.end ();
    }

  return 0;
}

