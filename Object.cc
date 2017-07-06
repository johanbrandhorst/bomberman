// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Object.cc
// Datum: 08/12/11

#include "Object.h"
#include "Input.h"
#include "Timer.h"
#include <string>
#include <typeinfo>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
 * Object
 */

Object::Object ()
{
  // Dummy-funktion
}

Object::Object (int square, Board* plan)
{
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  spelplan = plan;
}

Object::~Object ()
{
  // Dummy-funktion
}

int
Object::closest_square ()
{
  // 45 = spelplan->square_size.
  int closest_x = xpos / 45 + 1;
  int closest_y = ypos / 45 + 1;
  return closest_y * 100 + closest_x;
}

int
Object::middle_pixel_x (int square)
{
  // Ändrade spelplan->square_size till statisk siffra 45.
  return 45 / 2 + 1 + (square % 100 - 1) * 45;
}

int
Object::middle_pixel_y (int square)
{
  // Ändrade spelplan->square_size till statisk siffra 45.
  return 45 / 2 + 1 + (square / 100 - 1) * 45;
}

void
Object::draw ()
{
  // Dummy-funktion, överlagras längre ned.
}

void
Object::draw (int numb)
{
  // Dummy-funktion, överlagras längre ned.
}

void
Object::draw (int numb, Input& input)
{
  // Dummy-funktion, överlagras längre ned.
}

void
Object::destroy ()
{
  remove_object ();
}

void
Object::update ()
{
  draw ();
}

void
Object::update (int anim)
{
  draw (anim);
}

void
Object::update (Input& input)
{
  // Dummy-funktion
}

std::string
Object::get_color ()
{
  // Dummy-funktion
  return "useless";
}

int
Object::get_xpos ()
{
  return xpos;
}

int
Object::get_ypos ()
{
  return ypos;
}

Object*
Object::what_is (unsigned int square)
{
  // Kollar om rutan är upptagen i varje map/vector
  // och om så är fallet returnerar en pekare till objektet
  // på den rutan.

  if (spelplan->dynamic_objects.count (square))
    return spelplan->dynamic_objects.find (square)->second;

  if (spelplan->power_ups.count (square))
    return spelplan->power_ups.find (square)->second;

  if (spelplan->indestructible_walls.count (square))
    return spelplan->indestructible_walls.find (square)->second;

  return 0;
}

void
Object::insert_object ()
{
  // Kollar vilken sorts pekare som vill s�ttas in
  // och avgör utifrån den informationen i vilken map/vector
  // pekaren ska sättas in i, sätter sedan in objektet i den
  // mappen/vektorn.

  if (dynamic_cast<Bomb*> (this) != 0 ||
      dynamic_cast<Destructible_wall*> (this) != 0)
    spelplan->dynamic_objects.insert (pair<int, Object*>(closest_square (), this));

  if (dynamic_cast<Indestructible_wall*> (this) != 0)
    spelplan->indestructible_walls.insert (pair<int, Object*>(closest_square (), this));

  if (dynamic_cast<Power_up*> (this) != 0)
    spelplan->power_ups.insert (pair<int, Object*>(closest_square (), this));

  if (dynamic_cast<Player*> (this) != 0)
    spelplan->players.push_back (this);
}

void
Object::remove_object ()
{
  // Kollar vilken sorts pekare som vill tas bort
  // och avgör utifrån den informationen i vilken map/vector
  // pekaren ska tas bort ifrån, kallar sedan erase som i sin tur
  // kallar alla destruktorer neråt i kedjan.

  if (dynamic_cast<Bomb*> (this) != 0 ||
      dynamic_cast<Destructible_wall*> (this) != 0 ||
      dynamic_cast<Explosion*> (this) != 0)
    spelplan->dynamic_objects.erase (closest_square ());

  else if (dynamic_cast<Indestructible_wall*> (this) != 0)
    spelplan->indestructible_walls.erase (closest_square ());

  else if (dynamic_cast<Power_up*> (this) != 0)
    spelplan->power_ups.erase (closest_square ());

  // Loopar igenom listan med spelare och tar bort den som har samma
  // färg som objektet vi vill ta bort.
  else if (dynamic_cast<Player*> (this) != 0)
    for (vector<Object*>::iterator it = spelplan->players.begin (); it < spelplan->players.end (); it++)
      if ((dynamic_cast<Player*> (this))->get_color () == (dynamic_cast<Player*> (*it))->get_color ())
        // Specialfall om man vill ta bort det sista elementet i vektorn
        // Stoppar for-loopen så att det inte skapas ett segfault när
        // iteratorn vill utökas.
        if (it == spelplan->players.end () - 1)
        {
          spelplan->players.erase (it);
          break;
        }
        else
          spelplan->players.erase (it);
}

/*
 * Player
 */

Player::Player (int square, Board* plan, string col, int l)
{
  // Spelarens konstruktor, sätter alla datamedlemmar
  // till rätt värden.

  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  spelplan = plan;
  color = col;
  number_of_bombs = 1;
  bomb_radius = 2;
  speed = 3;
  animater = 0;
  direction = 'd';

  // Extra liv?
  lives = l;
  immune_timer = 0;

  // Kopierar dynamiskt data för keybinds från spelplanen.
  if (color == "White")
    {
      bindings.push_back (spelplan->bindings[0]);
      bindings.push_back (spelplan->bindings[1]);
      bindings.push_back (spelplan->bindings[2]);
      bindings.push_back (spelplan->bindings[3]);
      bindings.push_back (spelplan->bindings[4]);
    }
  else if (color == "Red")
    {
      bindings.push_back (spelplan->bindings[5]);
      bindings.push_back (spelplan->bindings[6]);
      bindings.push_back (spelplan->bindings[7]);
      bindings.push_back (spelplan->bindings[8]);
      bindings.push_back (spelplan->bindings[9]);
    }
  else if (color == "Blue")
    {
      bindings.push_back (spelplan->bindings[10]);
      bindings.push_back (spelplan->bindings[11]);
      bindings.push_back (spelplan->bindings[12]);
      bindings.push_back (spelplan->bindings[13]);
      bindings.push_back (spelplan->bindings[14]);
    }
  else if (color == "Green")
    {
      bindings.push_back (spelplan->bindings[15]);
      bindings.push_back (spelplan->bindings[16]);
      bindings.push_back (spelplan->bindings[17]);
      bindings.push_back (spelplan->bindings[18]);
      bindings.push_back (spelplan->bindings[19]);
    }
}

void
Player::drop_bomb ()
{
  // Skapar en bomb om det inte redan finns en på närmaste rutan
  // och om number_of_bombs > 0.
  if (number_of_bombs && (dynamic_cast<Bomb*>
    (what_is (closest_square ())) == 0
    && dynamic_cast<Explosion*> (what_is (closest_square ())) == 0))
  {
    number_of_bombs--;

    Object* p = new Bomb (closest_square (), this, spelplan);
    p->insert_object ();
  }
}

void
Player::move (Input& input)
{
  // Läser in vilka knappar som tryckts/är nedtryckta denna frame
  bool* keysHeld = input.getInput ();
  bool* keysPressed = input.getPressed ();

  // Information för kollisionshanteringen.
  int square = closest_square ();
  int xmove = 0;
  int ymove = 0;
  int middle_y = middle_pixel_y (square);
  int middle_x = middle_pixel_x (square);

  // Om bombknappen tryckts, kalla drop_bomb().
  if (keysPressed[bindings[0]])
  {
    drop_bomb ();
  }

  // Vänster
  if (keysHeld[bindings[1]])
  {
    // Om rutan till VÄNSTER om närmaste rutan inte har en bomb
    // eller en sorts vägg.
    if (dynamic_cast<Bomb*> (what_is (square - 1)) == 0 &&
      dynamic_cast<Wall*> (what_is (square - 1)) == 0)
    {
      // Om man står på mitten av rutan, gå till vänster.
      if (ypos == middle_y &&
          xpos == middle_x)
        xmove = -speed;
      // Om man inte står på mitten men står ovanför mitten
      // "hjälp till" runt hörnet genom att gå uppåt
      else if (ypos > middle_y)
        ymove = -speed;
      // Om man står under mitten, hjälp till
      // genom att gå nedåt.
      else if (ypos < middle_y)
        ymove = speed;
      // Om man inte står i mitten och man inte står ovanför
      // eller under mitten, gå vänster.
      else
        xmove = -speed;
    }
    // Om rutan till vänster om närmaste rutan *är* en vägg,
    // men vi står inte i mitten av rutan än.
    else if (xpos > middle_x)
      // Gå till vänster
      xmove = -speed;
  }

  // Höger, samma bas som vänster.
  if (keysHeld[bindings[2]])
  {
    if (dynamic_cast<Bomb*> (what_is (square + 1)) == 0 &&
      dynamic_cast<Wall*> (what_is (square + 1)) == 0)
    {
      if (ypos == middle_y && xpos == middle_x)
        xmove = speed;
      else if (ypos > middle_y)
        ymove = -speed;
      else if (ypos < middle_y)
        ymove = speed;
      else
        xmove = speed;
    }
    else if (xpos < middle_x)
      xmove = speed;
  }

  // Upp, samma bas som vänster.
  if (keysHeld[bindings[3]])
  {
    if (dynamic_cast<Bomb*> (what_is (square - 100)) == 0 &&
      dynamic_cast<Wall*> (what_is (square - 100)) == 0)
    {
      if (ypos == middle_y && xpos == middle_x)
        ymove = -speed;
      else if (xpos > middle_x)
        xmove = -speed;
      else if (xpos < middle_x)
        xmove = speed;
      else
        ymove = -speed;
    }
    else if (ypos > middle_y)
      ymove = -speed;
  }

  // Ner, samma bas som vänster.
  if (keysHeld[bindings[4]])
  {
    if (dynamic_cast<Bomb*> (what_is (square + 100)) == 0 &&
      dynamic_cast<Wall*> (what_is (square + 100)) == 0)
    {
      if (ypos == middle_y && xpos == middle_x)
        ymove = speed;
      else if (xpos > middle_x)
        xmove = -speed;
      else if (xpos < middle_x)
        xmove = speed;
      else
        ymove = speed;
    }
    else if (ypos < middle_y)
      ymove = speed;
  }

  // Hantera att man försöker gå åt två håll samtidigt
  // Om både xmove och ymove är satta, kompensera
  // genom att gå det håll som man INTE gick senaste framen.
  if (abs (xmove) + abs (ymove) > speed)
    if (lastmove == 'y')
      ymove = 0;
    else
      xmove = 0;

  // Den faktiskta rörelsen, gå antalet pixlar i riktingen som
  // bestämts ovan och sätt lastmove.
  if (xmove)
  {
    // Bestäm vilken riktning spelaren går
    if (xmove < 0)
      direction = 'l';
    else
      direction = 'r';

    lastmove = 'x';
    xpos += xmove;
  }
  else if (ymove)
  {
    // Bestäm vilken riktning spelaren går
    if (ymove < 0)
      direction = 'u';
    else
      direction = 'd';

    lastmove = 'y';
    ypos += ymove;
  }
}

void
Player::update (Input& input)
{
  if (immune_timer > 0)
    immune_timer--;

  // Rör spelaren beroende på input.
  move (input);

  // Om man står på mitten av en ruta och det finns
  // ett Power-up-objekt på rutan, kör upgrade på
  // den sortens Power-up.
  if (middle_pixel_x (closest_square ()) == xpos &&
      middle_pixel_y (closest_square ()) == ypos &&
      dynamic_cast<Power_up*> (what_is (closest_square ())) != 0)
    upgrade (what_is (closest_square ()));

  // Rita ut spelaren.
  draw (input);
}

void
Player::draw_helper (int y, Input& input)
{
  // Tar y, var på bilden som bilderna ska hämtas och ritar ut
  // beroende på vilket håll spelaren rör sig åt.

  // Skapa en bool-array för att se vilka knappar som trycks.
  bool* keysHeld = input.getInput ();

  // Om animater är 39, sätt till 0.
  if (animater == 39)
    animater = 0;

  // Om en knapp trycks ned starta animationen

  // Ner
  if (keysHeld[bindings[4]])
  {
    spelplan->background.drawSprite (spelplan->pic, 0 + 45 * (animater / 5), y, xpos - 23, ypos - 23, 45, 45);
    animater++;
    direction = 'd';
  }

  // Höger
  else if (keysHeld[bindings[2]])
  {
    spelplan->background.drawSprite (spelplan->pic, 360 + 45 * (animater / 5), y, xpos - 23, ypos - 23, 45, 45);
    animater++;
    direction = 'r';
  }

  // Upp
  else if (keysHeld[bindings[3]])
  {
    spelplan->background.drawSprite (spelplan->pic, 720 + 45 * (animater / 5), y, xpos - 23, ypos - 23, 45, 45);
    animater++;
    direction = 'u';
  }

  // Vänster
  else if (keysHeld[bindings[1]])
  {
    spelplan->background.drawSprite (spelplan->pic, 1080 + 45 * (animater / 5), y, xpos - 23, ypos - 23, 45, 45);
    animater++;
    direction = 'l';
  }

  // Om av rörelseknapparna är nedtryckt, ladda stillastående bild.
  else
  {
    // Ner
    if (direction == 'd')
      spelplan->background.drawSprite (spelplan->pic, 0, y, xpos - 23, ypos - 23, 45, 45);

    // Höger
    if (direction == 'r')
      spelplan->background.drawSprite (spelplan->pic, 360, y, xpos - 23, ypos - 23, 45, 45);

    // Upp
    if (direction == 'u')
      spelplan->background.drawSprite (spelplan->pic, 720, y, xpos - 23, ypos - 23, 45, 45);

    // Vänster
    if (direction == 'l')
      spelplan->background.drawSprite (spelplan->pic, 1080, y, xpos - 23, ypos - 23, 45, 45);
  }
}

void
Player::draw (Input& input)
{
  // Ritar ut spelaren  på planen, laddar från stora bilden
  // lagrad i Board och korrigerar för att våra koordinater
  // räknar från mitten och SDL från över vänstra hörnet.

  // Blinka om immune_timer > 0
  if (immune_timer % 5 <= 2)
  {
    if (color == "Red")
    {
      draw_helper (770, input);
    }
    else if (color == "White")
    {
      draw_helper (815, input);
    }
    else if (color == "Blue")
    {
      draw_helper (860, input);
    }
    else if (color == "Green")
    {
      draw_helper (905, input);
    }
  }
}

void
Player::upgrade (Object* new_power)
{
  // Uppgraderar en utav datamedlemmarna beroende på inparametern.
  if (dynamic_cast<Faster*> (new_power) != 0 && speed < 9)
    // 3 olika steg: 3 -> 5 -> 9.
    speed = speed * 2 - 1;

  else if (dynamic_cast<New_bomb*> (new_power) != 0)
    number_of_bombs++;

  else if (dynamic_cast<Larger_radius*> (new_power) != 0)
    bomb_radius++;

  // Förstör power-up-objektet.
  new_power->destroy ();

  // Spela Power-up ljudet
  spelplan->background.play (spelplan->audio[6], 0);
}

void
Player::add_bomb ()
{
  number_of_bombs += 1;
}

string
Player::get_color ()
{
  return color;
}

int
Player::get_bomb_radius ()
{
  return bomb_radius;
}

/*
 * Explosion
 */

Explosion::Explosion (int square, Player* dude, Board* plan)
{
  // Konstruktor, sätter datamedlemmar.
  // time representerar hur många frames explosionen
  // ska vara innan den tas bort.

  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  time = 30;
  spelplan = plan;
  owner = dude;
}

void
Explosion::insert_object ()
{
  // överlagrad funktion som tar bort objekt i mappen
  // dynamic_objects på samma ruta som explosionen och sedan
  // lägger in ett explosions-objekt på den rutan.
  if (what_is (closest_square ()) != 0)
    what_is (closest_square ())->remove_object ();

  spelplan->dynamic_objects.insert (pair<int, Object*>(closest_square (), this));
}

int
Explosion::distance (Player* dude)
{
  // Räknar ut största avståndet från explosionen till spelaren
  // i pixlar och returnerar som en int.
  return max (abs (xpos - dude->get_xpos ()), abs (ypos - dude->get_ypos ()));
}

void
Explosion::kill ()
{
  // Funktion som söker igenom spelarvektorn och kallar spelarens
  // destroy()-funktion, dvs dödar spelaren.

  // Skapa en temporär variabel som håller reda på antalet kills denna frame
  // och en som håller reda på om en spelare dog av sin egen explosion
  for (vector<Object*>::iterator it = spelplan->players.begin () ; it < spelplan->players.end ();)
    // Tillåter 5 pixlar extra så att spelaren som fysiskt är 45 pixlar
    // stor blir 35 pixlar stor (5 från varje sida). Om en spelare tas
    // bort kommer iteratorn automatiskt att peka på nästa element så
    // for loopen gör ingenting i det fallet, annars ökar den iteratorn.
    if (distance (dynamic_cast<Player*> (*it)) < (spelplan->square_size - 5))
    {
      if (dynamic_cast<Player*> (*it)->immune_timer == 0)
      {
        // Om spelaren bara har ett liv kvar, ta bort spelaren
        // och öka scoreboard med ett.
        if (dynamic_cast<Player*> (*it)->lives == 1)
	      {
          // Om ägaren till explosionen är den samma som explosionen dödar
          // sätt humiliation = true.
          if ((*it)->get_color () == owner->get_color ())
            spelplan->humiliation = true;

          // Om någon redan dött denna frame, ta bort en poäng från denna
          // spelare eftersom han fick en poäng innan
          if (spelplan->kills_this_frame)
		        spelplan->score[dynamic_cast<Player*>(*it)->get_color()] -= spelplan->kills_this_frame;

          // Lägg till poäng till alla andra spelare (Zatacka style)
          spelplan->add_points(dynamic_cast<Player*>(*it)->get_color ());
          (*it)->destroy ();

          // Öka antalet kills denna frame och totalt.
          spelplan->kills_this_frame++;
          spelplan->kills++;
	      }
	      else
	      {
	        // Annars sätt immun-timer och ta bort ett liv.
          dynamic_cast<Player*> (*it)->immune_timer = 100;
          dynamic_cast<Player*> (*it)->lives--;
          it++;
	      }
	    }
	    else
	      it++;
    }
    else
      it++;
}

int
Explosion::decrease_time ()
{
  // Funktion som körs varje frame och räknar ner explosionens tid.
  return time--;
}

void
Explosion::reset_time ()
{
  // Funktion som körs då en explosion upptäcker en annan explosion
  // och resettar tiden istället för att ta bort och skapa ett nytt objekt.
  time = 30;
}

void
Explosion::draw ()
{
  // Ritar ut explosionen, animerad beroende på kvarvarande tiden.
  spelplan->background.drawSprite (spelplan->pic, 9 * 45 - ((time - 1) / 5)*45, 1130, xpos - 23, ypos - 23, 45, 45);
}

void
Explosion::update ()
{
  // Kolla om tiden är 0, förstör då objektet
  // annars kör funktionen som försöker döda spelare.
  if (decrease_time ())
    kill ();
  else
    destroy ();

  // Rita ut objektet.
  draw ();
}

/*
 *Power_ups
 */

/*
 * Power_up
 * Faster
 */

Faster::Faster (int square, Board* plan)
{
  // Konstruktor
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  spelplan = plan;
}

void
Faster::draw (int anim)
{
  // Tar in en int som används för att bestämma varifrån
  // bilden hämtas och på så sätt animera bilden.
  spelplan->background.drawSprite (spelplan->pic, (anim / 5)*45, 950, xpos - 23, ypos - 23, 45, 45);
}

/*
 * Power_up
 * New_bomb
 */

New_bomb::New_bomb (int square, Board* plan)
{
  // Konstruktor
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  spelplan = plan;
}

void
New_bomb::draw (int anim)
{
  // Tar in en int som används för att bestämma varifrån
  // bilden hämtas och på så sätt animera bilden.
  spelplan->background.drawSprite (spelplan->pic, (anim / 5)*45, 995, xpos - 23, ypos - 23, 45, 45);
}

/*
 * Power_up
 * Larger_radius
 */

Larger_radius::Larger_radius (int square, Board* plan)
{
  // Konstruktor
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);
  spelplan = plan;
}

void
Larger_radius::draw (int anim)
{
  // Tar in en int som används för att bestämma varifrån
  // bilden hämtas och på så sätt animera bilden.
  spelplan->background.drawSprite
    (spelplan->pic, (anim / 5)*45, 1040, xpos - 23, ypos - 23, 45, 45);
}

/*
 * Bomb
 */

Bomb::Bomb (int square, Player* dude, Board* plan)
{
  // Konstruktor, hämtar information från sin ägare
  // dvs spelaren som skapade objektet.
  // time avser hur många frames bomben ska existera.
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);

  owner = dude;
  radius = dude->get_bomb_radius ();
  spelplan = plan;
  time = 100;
}

void
Bomb::explode ()
{
  // Funktion som söker runt sitt objekt och skapar
  // explosions objekt framtills den möter en vägg eller
  // en annan bomb.

  int r;

  for (int direction = 0; direction < 4; direction++)
    for (int i = 1; i <= radius; i++)
    {
      if (direction == 0)
        r = i;
      else if (direction == 1)
        r = 100 * i;
      else if (direction == 2)
        r = -i;
      else if (direction == 3)
        r = -100 * i;

      // Beräknas varje gång beroende på vilket håll
      // som genomsöks.
      unsigned int sq = closest_square () + r;

	    if (what_is (sq))
      {
        // Om en ind_wall hittas, avbryt loopen i denna riktning.
        if (dynamic_cast<Indestructible_wall*> (what_is (sq)) != 0)
          break;
        // Om en vägg eller Power-up hittas, skapa nytt explosions-
        // objekt och sätt in det i mappen (insert-object() är
        // överlagrat för att ta bort det gamla objektet på rutan först)
        // och avbryt loopen i denna riktning.
        else if (dynamic_cast<Destructible_wall*> (what_is (sq)) != 0 or
          dynamic_cast<Power_up*> (what_is (sq)) != 0)
        {
          Object* p = new Explosion (sq, owner, spelplan);
          p->insert_object ();
          break;
        }
        // Om en bomb hittas, sätt tiden som den bomben har kvar
        // till 0 så den sprängs nästa frame och avbryt loopen
        // i denna riktning.
        else if (dynamic_cast<Bomb*> (what_is (sq)) != 0)
        {
          dynamic_cast<Bomb*> (what_is (sq))->set_time (0);
          break;
        }
        // Om en explosion hittas, resetta dess tid istället
        // för att ta bort och skapa nytt objekt.
        else if (dynamic_cast<Explosion*> (what_is (sq)) != 0)
          dynamic_cast<Explosion*> (what_is (sq))->reset_time ();
      }
      // Om det inte finns något på rutan, sätt ut ett explosions-
      // objekt på rutan.
      else
      {
        Object* p = new Explosion (sq, owner, spelplan);
        p->insert_object ();
      }
    }

  // Lägg till en bomb till ägaren.
  owner->add_bomb ();

  // Spela explosionsljudet
  spelplan->background.play (spelplan->audio[3], 0);

  // Skapa till sist en explosion på den egna rutan, som kommer
  // ta bort bomb-objektet.
  Object* pp = new Explosion (closest_square (), owner, spelplan);
  pp->insert_object ();
}

int
Bomb::decrease_time ()
{
  // Räkna ner tiden.
  return time--;
}

void
Bomb::set_time (int t)
{
  // Sätt tiden.
  time = t;
}

void
Bomb::update ()
{
  // Spräng bombem om tiden är 0,
  // annars rita bara ut den.
  if (!decrease_time ())
    explode ();

  draw ();
}

void
Bomb::draw ()
{
  // Ritar ut explosionen, animerad beroende på kvarvarande tiden.
  spelplan->background.drawSprite (spelplan->pic, 9 * 45 - ((time - 1) / 10)*45 , 1175, xpos - 23, ypos - 23, 45, 45);
}

/*
 * Wall
 */

/*
 * Wall
 * Destructible
 */

Destructible_wall::Destructible_wall (int square, Board* plan)
{
  // Konstruktor
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);

  spelplan = plan;
}

void
Destructible_wall::draw ()
{
  // Rita ut väggen
  spelplan->background.drawSprite (spelplan->pic, 0, 725, xpos - 23, ypos - 23, 45, 45);
}

/*
 * Wall
 * Indestructible
 */

Indestructible_wall::Indestructible_wall (int square, Board* plan)
{
  // Konstruktor
  ypos = middle_pixel_y (square);
  xpos = middle_pixel_x (square);

  spelplan = plan;
}

void
Indestructible_wall::draw ()
{
  // Rita ut väggen
  spelplan->background.drawSprite (spelplan->pic, 45, 725, xpos - 23, ypos - 23, 45, 45);
}
