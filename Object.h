// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Object.h
// Datum: 08/12/11

#ifndef OBJECT_H
#define OBJECT_H
#include "Board.h"
#include "Input.h"
#include "SDL/SDL.h"
#include <stdexcept>
#include <string>
#include <vector>

class Object
{
 public:

  Object ();
  Object (int, Board*);

  virtual ~Object ();
  virtual int closest_square ();
  virtual int middle_pixel_x (int);
  virtual int middle_pixel_y (int);

  virtual void draw (); // Målar objektet på spelplanen
  virtual void draw (int);
  virtual void draw (int, Input&);

  virtual void destroy (); // Förstör objektet (spelplanen och i minnet),

  virtual void update (); // Virtual, överlagras i underklasser
  virtual void update (int);
  virtual void update (Input&);

  virtual std::string get_color();
  virtual int get_xpos ();
  virtual int get_ypos ();

  virtual Object* what_is (unsigned int);
  virtual void insert_object ();
  virtual void remove_object ();

 protected:
  int xpos;
  int ypos;
  Board* spelplan;
};

class Power_up : public Object
{
  // Kompilatorgenererad destruktor
};

class Faster : public Power_up
{
 public:
  Faster (int, Board*);
  // Kompilatorgenereraddestruktor

  // Överlagrade funktioner
  void draw (int);
};

class New_bomb : public Power_up
{
 public:
  New_bomb (int, Board*);
  // Kompilatorgenererad destruktor

  // Överlagrade funktioner
  void draw (int);
};

class Larger_radius : public Power_up
{
 public:
  Larger_radius (int, Board*);
  // Kompilatorgenererad destruktor

  // Överlagrade funktioner
  void draw (int);
};

class Player : public Object
{
 public:

  Player (int, Board*, std::string, int);
  // Medlemsfunktioner
  void drop_bomb ();
  void move (Input&);
  int get_bomb_radius ();
  void upgrade (Object*);
  void add_bomb();

  // Överlagrade funktioner
  void update (Input&);
  void draw_helper(int, Input&);
  void draw (Input&);
  std::string get_color ();

  // Extra liv
  friend class Explosion;

 private:
  // Datamedlemmar

  std::vector<SDLKey> bindings;
  int speed;
  int number_of_bombs;
  int bomb_radius;
  int animater;
  std::string color;

  char lastmove;
  char direction;

  // Extra liv
  int lives;
  int immune_timer;
};

class Explosion : public Object
{
 public:
  Explosion (int, Player*, Board*);
  // Kompilatorgenererad destruktor

  // Medlemsfunktioner
  int distance (Player*);
  void kill ();
  int decrease_time ();
  void reset_time();

  // Överlagrade funktioner
  void draw ();
  void update ();
  void insert_object();

 private:
  int time;
  Player* owner;
};

class Bomb : public Object
{
 public:
  Bomb (int, Player*, Board*);

  // Medlemsfunktioner
  void explode ();
  int decrease_time ();
  void set_time(int);

  // Överlagrade funktioner
  void update ();
  void draw ();

 private:
  int radius;
  int time;
  Player* owner;
};

class Wall : public Object
{
  // Kompilatorgenererad konstruktor och destruktor
};

class Destructible_wall : public Wall
{
 public:
  Destructible_wall (int, Board*);
  // Kompilatorgenererad destruktor

  // Överlagrade funktioner
  void draw ();
};

class Indestructible_wall : public Wall
{
 public:
  Indestructible_wall (int, Board*);
  // Kompilatorgenererad destruktor

  // Överlagrade funktioner
  void draw ();
};

#endif
