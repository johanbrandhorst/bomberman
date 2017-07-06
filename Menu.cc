// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Menu.cc
// Datum: 08/12/11

#include "Menu.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include "SDL/SDL.h"
using namespace std;

Menu::Menu ()
{
  // Konstruktor

  // Datamedlemmar sätts till ett standardvärde
  lives = 1;
  tema = 1;
  number_of_players = 2;
  bana = 1;
  fps = 60;

  // Skapa ett nytt Board-objekt
  current_board = new Board (900, 675, 255, 255, 255, tema);

  // Om det gick att ladda settings från new_settings, gör
  // inget mer, om det inte gick, ladda default.
  if (!load_settings ("new_settings.txt"))
    load_settings ("default.txt");

  // Sätt in de olika banorna i ban-vektorn
  banor.push_back ("bana1.txt");
  banor.push_back ("bana2.txt");
  banor.push_back ("bana3.txt");
  banor.push_back ("bana4.txt");
  banor.push_back ("bana5.txt");

  // Sätt storleken och bakgrundsfärgen på startmenyn
  startup.width = 900;
  startup.height = 675;
  startup.setBGColor (255, 255, 255);
  startup.Init ();
}

void
Menu::create_board (const char* ban)
{
  // Funktion som sätter in väggar och objekt på rätt ställen
  // utifrån en textfil. Sätter ut Power-ups på lottade ställen
  // under dest_wall lådor.

  // Char som används för att tolka nästa tecken
  char c;

  // Börjar på ruta 0101
  int square = 101;

  // Använd tiden som seed för att lotta ut var power-ups ska vara
  srand (time (0));

  // Skapa och öppna en in-ström
  ifstream is;
  is.open (ban);

  // Så länge strömmen inte nått problem eller slutet på filen
  while (is.good ())
	{
      // Hämta nästa tecken
      is.get (c);

      // Om c är ett mellanslag, gå tillbaka ett
      // steg och börja loopen igen
      if (c == ' ')
				square--;

      // Om c är ett x, sätt ut indestructible_wall
      else if (c == 'x')
			{
				Object* iw = new Indestructible_wall (square, current_board);
				iw->insert_object ();
			}

      // Om c är ett d, sätt ut ny destructible_wall och
      // slumpa ut en power-up under den.
      // ca 4% chans för en "Faster", väntevärde = 7
      // ca 6% chans för en "New_Bomb", väntevärde = 10
      // ca 6% chans för en "Larger_radius", väntevärde = 10
      else if (c == 'd')
			{
				Object* dw = new Destructible_wall (square, current_board);
				dw->insert_object ();

				int seed;
				// En siffra mellan 1 och 50
				if (bana == 1)
					seed = 50;
				else if (bana == 2)
					seed = 40;
				else if (bana == 3)
					seed = 40;
				else if (bana == 4)
					seed = 40;
				else if (bana == 5)
					seed = 30;

				int random = rand () % seed + 1;

				// Slumpa ut power-ups.
				if (random == 1 || random == 2)
				{
					Object* pu = new Faster (dw->closest_square (), current_board);
					pu->insert_object ();
				}
				else if (random >= 3 && random < 7)
				{
					Object* pu = new New_bomb (dw->closest_square (), current_board);
					pu->insert_object ();
				}
				else if (random >= 7 && random < 11)
				{
					Object* pu = new Larger_radius (dw->closest_square (), current_board);
					pu->insert_object ();
				}
			}

      // Om c är newline, fortsätt till nästa rad.
      else if (c == '\n')
				square += 84;

      // Gå till nästa ruta.
      square++;
    }

  // Stäng strömmen
  is.close ();
}

void
Menu::set_key (int index)
{
  // Skapa ett event som vi kan anv�nda
  SDL_Event keyevent;

  // T�mmer Event-k�n
  while (SDL_PollEvent (&keyevent))
    {
    }

  // V�ntar p� n�sta event
  SDL_WaitEvent (&keyevent);

  // Beroende p� vilken typ av event det var,
  // s�tt antingen knappen till den korresponderande
  // knappen eller avbryt switch-satsen.
  switch (keyevent.type)
    {
    case SDL_KEYDOWN:
      if (keyevent.key.keysym.sym != SDLK_ESCAPE)
	{
	  // S�tt bindings till senast tryckta knappen
	  current_board->bindings[index] =
	    keyevent.key.keysym.sym;
	  // Uppdatera bindings_text.
	  current_board->bindings_text[index] =
	    current_board->convert
	    (keyevent.key.keysym.sym);
	}
      break;

    case SDL_QUIT:
      exit (EXIT_SUCCESS);
      break;

    default:
      break;
    }
}

void
Menu::draw_keys (string player, int pl, int ypos)
{
  // Ritar ut knapparna i keybindings-menyn

  // B�rjar med xpos 100 och ritar sedan relativt den.
  int xpos = 100;

  startup.drawText
    (player, 24, xpos, ypos - 50, 0, 0, 0);

  // Bomb
  startup.drawSprite
    (current_board->pic, 100, 1220, xpos, ypos, 50, 50);
  startup.drawText
    (current_board->bindings_text[pl],
     16, xpos + 55, ypos + 12, 0, 0, 0);

  // Left
  startup.drawSprite
    (current_board->pic, 150, 1220, xpos + 150, ypos, 50, 50);
  startup.drawText
    (current_board->bindings_text[pl + 1],
     16, xpos + 205, ypos + 12, 0, 0, 0);

  // Right
  startup.drawSprite
    (current_board->pic, 200, 1220, xpos + 300, ypos, 50, 50);
  startup.drawText
    (current_board->bindings_text[pl + 2],
     16, xpos + 355, ypos + 12, 0, 0, 0);

  // Up
  startup.drawSprite
    (current_board->pic, 250, 1220, xpos + 450, ypos, 50, 50);
  startup.drawText
    (current_board->bindings_text[pl + 3],
     16, xpos + 505, ypos + 12, 0, 0, 0);

  // Down
  startup.drawSprite
    (current_board->pic, 300, 1220, xpos + 600, ypos, 50, 50);
  startup.drawText
    (current_board->bindings_text[pl + 4],
     16, xpos + 655, ypos + 12, 0, 0, 0);
}

void
Menu::draw_settings (string setting, string number, int ypos)
{
  //Text
  startup.drawText
    (setting, 24, 220, ypos, 0, 0, 0);

  // Minus
  startup.drawSprite
    (current_board->pic, 0, 1220, 500, ypos - 10, 50, 50);

  // Value
  startup.drawText
    (number, 24, 565, ypos, 0, 0, 0);

  // Plus
  startup.drawSprite
    (current_board->pic, 50, 1220, 600, ypos - 10, 50, 50);
}

string
Menu::int_to_string (int str)
{
  stringstream out;
  out << str;
  return out.str ();
}

void
Menu::start_menu ()
{
  // Skapa ett event
  SDL_Event event;

  // Rita start-bakgrunden
  startup.start ();

  // S�tt datainformation f�r anv�ndning i menyerna
  int menux = 350, menuy = 350, menuw = 200, menuh = 50, loadtime = 0;
  int savetime = 0;

  bool start_game = false;
  bool settings = false;
  bool keybinds = false;
  bool load_success = true;

  while (!start_game)
    {
      int x = 0, y = 0;

      // Rita ut backgrunden s� l�nge vi inte �r i keybinds menyn
      if (!keybinds)
	startup.drawSprite (current_board->pic, 0, 0, 0, 0, 900, 675);
      else
	startup.drawSprite (current_board->pic, 900, 0, 0, 0, 900, 675);

      // Omvandla siffror till strings. Anv�nds i settings.
      string string_of_lives = int_to_string (lives);
      string string_of_players = int_to_string (number_of_players);
      string string_bana = int_to_string (bana);
      string string_tema = int_to_string (tema);
      string string_fps = int_to_string (fps);


      // Start-menyn.
      if (!settings && !keybinds)
	{
	  startup.drawSprite
	    (current_board->pic, 1600, 675, menux,
	     menuy, menuw, menuh);
	  startup.drawSprite
	    (current_board->pic, 1400, 675, menux,
	     menuy + menuh * 3 / 2, menuw, menuh);
	  startup.drawSprite
	    (current_board->pic, 1000, 675, menux,
	     menuy + 3 * menuh, menuw, menuh);
	}

      // Back-knapp
      if ((settings && !keybinds) or (!settings && keybinds))
	startup.drawSprite
	  (current_board->pic, 400, 675, 620, 620, menuw, menuh);

      // Keybindings-menyn
      if (keybinds)
	{
	  // Player 1 Bilder (Red)
	  draw_keys ("White", 0, 100);

	  // Player 2 Bilder (White)
	  draw_keys ("Red", 5, 250);

	  // Player 3 Bilder (Blue)
	  draw_keys ("Blue", 10, 400);

	  // Player 4 Bilder (Green)
	  draw_keys ("Green", 15, 550);
	}

      // Settings-menyn
      if (settings)
	{
	  // Load/Save/Default Settings
	  startup.drawSprite
	    (current_board->pic, 800, 675, 100, 250, menuw, menuh);
	  startup.drawSprite
	    (current_board->pic, 1200, 675, 350, 250, menuw, menuh);
	  startup.drawSprite
	    (current_board->pic, 600, 675, 600, 250, menuw, menuh);

	  // Lives
	  draw_settings ("Player Lives:", string_of_lives, 320);

	  // Number of players:
	  draw_settings ("Number of Players:", string_of_players, 380);

	  // Bana
	  draw_settings ("Map:", string_bana, 440);

	  // Tema
	  draw_settings ("Theme:", string_tema, 500);

	  // FPS
	  draw_settings ("Max FPS:", string_fps, 560);

	  //Keybindings-knapp
	  startup.drawSprite
	    (current_board->pic, 1600, 725, 400, 620, 200, 50);

	  // Load successful meddelande
	  if (loadtime > 0)
	    {
	      if (load_success)
		startup.drawText
		  ("Load Successful!", 24, 10, 640, 0, 0, 0);
	      else
		{
		  startup.drawText
		    ("Load failed!", 24, 10, 640, 0, 0, 0);
		  load_success = true;
		}

	      loadtime--;
	    }

	  // Save successful meddelande
	  if (savetime > 0)
	    {
	      startup.drawText
		("Save Successful!", 24, 10, 640, 0, 0, 0);
	      savetime--;
	    }
	}


      // Knapptryckningshantering

      if (SDL_PollEvent (&event))
	{
	  // Om v�nster knapp tryckts
	  if (event.type == SDL_MOUSEBUTTONUP &&
	      event.button.button == SDL_BUTTON_LEFT)
	    {
	      // S�tt koordinaterna f�r knapptrycket
	      x = event.button.x;
	      y = event.button.y;

	      // Back-knapp
	      if ((settings && !keybinds) or (keybinds && !settings))
		{
		  if (y > 620 && y < 670 && x > 620 && x < 820)
		    {
		      if (!settings && keybinds)
			{
			  settings = true;
			  keybinds = false;
			}
		      else
			{
			  settings = false;
			  keybinds = false;
			}
		    }
		}

	      // Settings-meny
	      if (settings && !keybinds)
		{
		  // Load/Save/Default-knappar
		  if (y > 250 && y < 300)
		    {
		      // Load
		      if (x > 100 && x < 300)
			{
			  if (load_settings ("new_settings.txt"))
			    load_success = true;
			  else
			    load_success = false;
			  loadtime = 60;
			}

		      // Save
		      else if (x > 350 && x < 550)
			if (save_settings ())
			  savetime = 60;

		      // Default
		      if (x > 600 && x < 900)
			if (load_settings ("default.txt"))
			  loadtime = 60;
		    }

		  // Lives +,- knappar
		  else if (y > 310 && y < 360)
		    {
		      if (x > 600 && (x < 650) && lives < 3)
			lives++;
		      else if (x > 500 && x < 550 && lives > 1)
			lives--;
		    }

		  // Number of players +,- knappar
		  else if (y > 370 && y < 420)
		    {
		      if (x > 600 && (x < 650) && number_of_players < 4)
			number_of_players++;
		      else if (x > 500 && x < 550 && number_of_players > 2)
			number_of_players--;
		    }

		  // Bana +,- knappar
		  else if (y > 430 && y < 480)
		    {
		      if (x > 600 && (x < 650) && bana < 5)
			bana++;
		      else if (x > 500 && x < 550 && bana > 1)
			bana--;
		    }

		  // Tema +,- knappar
		  else if (y > 490 && y < 540)
		    {
		      if (x > 600 && x < 650 && tema < 4)
			tema++;
		      else if (x > 500 && x < 550 && tema > 1)
			tema--;
		    }

		  // FPS +,- knappar
		  else if (y > 550 && y < 600)
		    {
		      if (x > 600 && x < 650 && fps < 60)
			fps += 10;
		      else if (x > 500 && x < 550 && fps > 30)
			fps -= 10;
		    }

		  // Keybindings-knapp
		  else if (y > 620 && y < 670 && x > 400 && x < 600)
		    {
		      keybinds = true;
		      settings = false;
		    }
		}

	      // Keybinds-meny
	      if (!settings && keybinds)
		{
		  // Player 1 (Red)
		  if (y > 100 && y < 150)
		    {
		      if (x > 100 && x < 150)
			set_key (0);
		      else if (x > 250 && x < 300)
			set_key (1);
		      else if (x > 400 && x < 450)
			set_key (2);
		      else if (x > 550 && x < 600)
			set_key (3);
		      else if (x > 700 && x < 750)
			set_key (4);
		    }

		  // Player 2 (White)
		  else if (y > 250 && y < 300)
		    {
		      if (x > 100 && x < 150)
			set_key (5);
		      else if (x > 250 && x < 300)
			set_key (6);
		      else if (x > 400 && x < 450)
			set_key (7);
		      else if (x > 550 && x < 600)
			set_key (8);
		      else if (x > 700 && x < 750)
			set_key (9);
		    }

		  // Player 3 (Blue)
		  else if (y > 400 && y < 450)
		    {
		      if (x > 100 && x < 150)
			set_key (10);
		      else if (x > 250 && x < 300)
			set_key (11);
		      else if (x > 400 && x < 450)
			set_key (12);
		      else if (x > 550 && x < 600)
			set_key (13);
		      else if (x > 700 && x < 750)
			set_key (14);
		    }

		  // Player 4 (Green)
		  else if (y > 550 && y < 600)
		    {
		      if (x > 100 && x < 150)
			set_key (15);
		      else if (x > 250 && x < 300)
			set_key (16);
		      else if (x > 400 && x < 450)
			set_key (17);
		      else if (x > 550 && x < 600)
			set_key (18);
		      else if (x > 700 && x < 750)
			set_key (19);
		    }
		}

	      // Start-meny
	      if (!settings && !keybinds)
		{
		  if (x > menux && (x < menux + menuw))
		    {
		      // Start-game
		      if (y > menuy + 0 * menuh && (y < menuy + 1 * menuh))
			start_game = true;
		      // Settings
		      else if (y > menuy + menuh * 3 / 2 && (y < menuy + menuh * 5 / 2))
			settings = true;
		      // Quit
		      else if (y > menuy + menuh * 3 && (y < menuy + menuh * 4))
			exit (EXIT_SUCCESS);
		    }
		}

	    }
	  // Om avsluta tryckts, avsluta
	  else if (event.type == SDL_QUIT)
	    exit (EXIT_SUCCESS);
	}

      // Uppdatera spelplanen
      startup.end ();
    }
}

void
Menu::start_game ()
{
  // Konvertera stringarna i banor-vektorn till
  // const char* arrayer
  const char* bana2 = banor[bana - 1].c_str ();

  // S�tt tema, l�s in banan, uppdatera sk�rmen
  current_board->set_tema (tema);
  create_board (bana2);
  current_board->background.start ();

  // Skapar alla spelare
  if (number_of_players >= 2)
    {
      // S�tter in tv� spelare p� motst�ende sidor
      Object* np = new Player (202, current_board, "Red", lives);
      np->insert_object ();
      Object* np2 = new Player (1414, current_board, "White", lives);
      np2->insert_object ();
    }
  if (number_of_players >= 3)
    {
      // �vre h�gra h�rnet
      Object* np3 = new Player (214, current_board, "Blue", lives);
      np3->insert_object ();
    }
  if (number_of_players == 4)
    {
      // Nedre v�nstra h�rnet
      Object* np4 = new Player (1402, current_board, "Green", lives);
      np4->insert_object ();
    }

  // Spela "Play" ljudet.
  current_board->background.play (current_board->audio[0], 0);
}

bool
Menu::load_settings (string file)
{
  // L�ser in inst�llningar fr�n en sparad fil och
  // �ndrar spelets datamedlemmar till dess v�rden.

  // Skapar element att ladda in fr�n str�mmen, en siffra och
  // tv� strings
  int siffra = 0;
  string key, key2;

  // Konverterar inparametern till const char* array
  const char* file2 = file.c_str ();

  // Skapar och �ppnar en instr�m fr�n filnamnet
  ifstream is;
  is.open (file2);

  // Om str�mmen �r �ppen och inte vid slutet av filen
  if (is.good ())
    {
      // lives
      is >> siffra;
      lives = siffra;

      // number_of_players
      is >> siffra;
      number_of_players = siffra;

      // bana
      is >> siffra;
      bana = siffra;

      // temat
      is >> siffra;
      tema = siffra;

      // fps;
      is >> siffra;
      fps = siffra;

      // F�r varje element i bindings_text skriv �ver datan p�
      // plats i med data fr�n str�mmen.
      for (unsigned int i = 0; i < current_board->bindings_text.size (); i++)
	{
	  // Ladda in f�rsta str�ngen
	  is >> key;

	  // Om det finns ett mellanslag direkt efter f�rsta str�ngen
	  // ladda d� in n�sta str�ng till key2 och s�tt datan till
	  // en addition av de b�da str�ngarna.
	  if (is.peek () == ' ')
	    {
	      is >> key2;
	      current_board->bindings_text[i] = key + " " + key2;
	    }

	  // Annars ladda in f�rsta str�ngen i bindings_text
	  else
	    current_board->bindings_text[i] = key;

	  // K�r funktionen deconvert f�r att �vers�tta texten som sattes
	  // in i bindings_text till faktiska SDLKey objekt och
	  // skriv �ver det som redan finns i bindings.
	  current_board->bindings[i] = current_board->deconvert
	    (current_board->bindings_text[i]);
	}

      // St�ng str�mmen.
      is.close ();
    }
  else
    // Om det inte gick att �ppna filen, returnera false
    return false;

  // Efter att inladdning avslutats, returnera true
  return true;
}

bool
Menu::save_settings ()
{
  // Funktion som sparar nuvarande inst�llningar p� fil

  // Skapa en str�m och �ppna str�mmen. Om new_settings inte finns
  // skapas den filen, om new_settings finns tas f�rst all data
  // i den filen bort.
  ofstream of;
  of.open ("new_settings.txt", ios::trunc);

  // Om det gick att �ppna filen
  if (of.is_open ())
    {
      // Skriv ut datamedlemmarna, separerade med mellanslag.
      of <<
	lives << " " << number_of_players << " " <<
	bana << " " << tema << " " << fps;

      // F�r varje element i bindings_text, skriv ut datan,
      // separerade av newlines.
      for (unsigned int i = 0; i < current_board->bindings_text.size (); i++)
	of << "\n" << current_board->bindings_text[i];

      // St�ng str�mmen
      of.close ();
    }
  else
    // Gick det inte att �ppna filen, returnera false
    return false;

  // Efter att sparning skett, returnera true
  return true;
}

void
Menu::update (Input& input, int anim)
{
  // Ritar f�rst ut bakgrunden till spelet.
  current_board->background.drawSprite
    (current_board->pic, 600, 1100, 0, 0, 675, 675);

  // Rita ut sido-banner
  current_board->background.drawSprite
    (current_board->pic, 1500, 1100, 675, 0, 225, 675);

  // Rita ut scoreboard
  current_board->display_points(number_of_players);

  // K�r alla objekts update-funktioner

  map<int, Object*>::iterator it;

  for (it = current_board->indestructible_walls.begin ();
       it != current_board->indestructible_walls.end (); it++)
    it->second->update ();

  for (it = current_board->power_ups.begin ();
       it != current_board->power_ups.end (); it++)
    it->second->update (anim);

  for (it = current_board->dynamic_objects.begin ();
       it != current_board->dynamic_objects.end (); it++)
    it->second->update ();

  for (vector<Object*>::iterator it = current_board->players.begin ();
       it != current_board->players.end (); it++)
    (*it)->update (input);
}

void
Menu::finished ()
{
  // Funktion som k�rs i slutet av spelet

  // Om det inte finns n�gra spelare kvar blev spelet lika
  if (current_board->players.size () == 0)
    {
      current_board->background.drawText
	("THE GAME IS A", 24, 680, 350, 255, 255, 255);
      current_board->background.drawText
	("DRAW!", 45, 680, 380, 255, 255, 255);
    }
  // Om det finns en spelare kvar, kora en vinnare!
  else
    {
      current_board->background.drawText
	("THE WINNER IS: ", 24, 680, 350, 255, 255, 255);
      current_board->background.drawText
	(current_board->players[0]->get_color (),
	 45, 680, 380, 255, 255, 255);
    }

  // Rita ut "Menu" och "Restart" -knappar.
  current_board->background.drawSprite
    (current_board->pic, 200, 675, 685, 550, 200, 50);
  current_board->background.drawSprite
    (current_board->pic, 0, 675, 685, 615, 200, 50);

  // Skapa ett event f�r att hantera knapptryckningar och
  // tv� int f�r att hantera positioner, p� samma s�tt som
  // i menyerna.
  SDL_Event event;
  int x = 0, y = 0;

  if (SDL_PollEvent (&event))
    {
      if (event.type == SDL_MOUSEBUTTONDOWN &&
	  event.button.button == SDL_BUTTON_LEFT)
	{
	  x = event.button.x;
	  y = event.button.y;

	  // Om n�gon av knapparna tryckts
	  if (x > 685 && x < 880)
	    {
	      // Restart-knapp
	      if (y > 550 && y < 600)
		{
		  current_board->kills = 0;
		  game_finished = false;
		  current_board->clear ();
		  start_game ();
		}

	      // Meny-knapp, cleara spelplanen
	      if (y > 615 && y < 665)
		{
		  current_board->kills = 0;
		  game_finished = false;
		  current_board->clear ();
		  current_board->reset_points();
		  start_menu ();
		  start_game ();
		}
	    }
	}
      else if (event.type == SDL_QUIT)
	exit (EXIT_SUCCESS);

      else if (event.type == SDL_KEYUP)
	{
	  if (event.key.keysym.sym == SDLK_RETURN)
	    {
	      current_board->kills = 0;
	      game_finished = false;
	      current_board->clear ();
	      start_game ();
	    }
	  else if (event.key.keysym.sym == SDLK_ESCAPE)
	    {
	      current_board->kills = 0;
	      game_finished = false;
	      current_board->clear ();
	      current_board->reset_points();
	      start_menu ();
	      start_game ();
	    }
	}
    }
}

void
Menu::paused ()
{
  // Funktion som k�rs om spelet pausas

  // Rita ut "Resume", "Restart" och "Menu" -knappar.
  // Resume
  current_board->background.drawSprite
    (current_board->pic, 1600, 775, 685, 485, 200, 50);
  // Restart
  current_board->background.drawSprite
    (current_board->pic, 200, 675, 685, 550, 200, 50);
  // Menu
  current_board->background.drawSprite
    (current_board->pic, 0, 675, 685, 615, 200, 50);

  // Skapa ett event f�r att hantera knapptryckningar och
  // tv� int f�r att hantera positioner, p� samma s�tt som
  // i menyerna.
  SDL_Event event;
  int x = 0, y = 0;

  if (SDL_PollEvent (&event))
    {
      if (event.type == SDL_MOUSEBUTTONDOWN &&
	  event.button.button == SDL_BUTTON_LEFT)
	{
	  x = event.button.x;
	  y = event.button.y;

	  // Om n�gon av knapparna tryckts
	  if (x > 685 && x < 880)
	    {
	      // Resume-knapp
	      if (y > 485 && y < 535)
		game_paused = false;

	      // Restart-knapp
	      else if (y > 550 && y < 600)
		{
		  game_paused = false;
		  game_finished = false;
		  current_board->clear ();
		  start_game ();
		}

	      // Meny-knapp, cleara spelplanen
	      else if (y > 615 && y < 665)
		{
		  game_paused = false;
		  game_finished = false;
		  current_board->clear ();
		  current_board->reset_points();
		  start_menu ();
		  start_game ();
		}
	    }
	}
      else if (event.type == SDL_QUIT)
	exit (EXIT_SUCCESS);

      else if (event.type == SDL_KEYUP)
	{
	  // Restarta spelet
	  if (event.key.keysym.sym == SDLK_RETURN)
	    {
	      current_board->kills = 0;
	      game_paused = false;
	      game_finished = false;
	      current_board->clear ();
	      start_game ();
	    }

	  // Resumea spelet
	  else if (event.key.keysym.sym == SDLK_ESCAPE)
	    game_paused = false;
	}
    }
}

