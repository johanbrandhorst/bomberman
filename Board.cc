// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Board.cc
// Datum: 08/12/11

#include <map>
#include <vector>
#include <typeinfo>
#include <sstream>
#include "SDL/SDL.h"
#include "Board.h"
#include "Object.h"
using namespace std;

SDLKey
Board::deconvert (string key)
{
  // En funktion som konverterar en text-sträng till
  // en SDLKey, används i menyn för att kunna spara och
  // ladda från en fil. Eftersom C++ inte stödjer switch-satser
  // får string-objekt fick det bli en massa if istället.

  if (key == "Backspace")
    return SDLK_BACKSPACE;

  else if (key == "Tab")
    return SDLK_TAB;

  else if (key == "Return")
    return SDLK_RETURN;

  else if (key == "Space")
    return SDLK_SPACE;


  else if (key == "+")
    return SDLK_PLUS;

  else if (key == ",")
    return SDLK_COMMA;

  else if (key == "-")
    return SDLK_MINUS;

  else if (key == ".")
    return SDLK_PERIOD;


  else if (key == "A")
    return SDLK_a;

  else if (key == "B")
    return SDLK_b;

  else if (key == "C")
    return SDLK_c;

  else if (key == "D")
    return SDLK_d;

  else if (key == "E")
    return SDLK_e;

  else if (key == "F")
    return SDLK_f;

  else if (key == "G")
    return SDLK_g;

  else if (key == "H")
    return SDLK_h;

  else if (key == "I")
    return SDLK_i;

  else if (key == "J")
    return SDLK_j;

  else if (key == "K")
    return SDLK_k;

  else if (key == "L")
    return SDLK_l;

  else if (key == "M")
    return SDLK_m;

  else if (key == "N")
    return SDLK_n;

  else if (key == "O")
    return SDLK_o;

  else if (key == "P")
    return SDLK_p;

  else if (key == "Q")
    return SDLK_q;

  else if (key == "R")
    return SDLK_r;

  else if (key == "S")
    return SDLK_s;

  else if (key == "T")
    return SDLK_t;

  else if (key == "U")
    return SDLK_u;

  else if (key == "V")
    return SDLK_v;

  else if (key == "W")
    return SDLK_w;

  else if (key == "X")
    return SDLK_x;

  else if (key == "Y")
    return SDLK_y;

  else if (key == "Z")
    return SDLK_z;

  else if (key == "Delete")
    return SDLK_DELETE;



  else if (key == "0")
    return SDLK_KP0;

  else if (key == "1")
    return SDLK_KP1;

  else if (key == "2")
    return SDLK_KP2;

  else if (key == "3")
    return SDLK_KP3;

  else if (key == "4")
    return SDLK_KP4;

  else if (key == "5")
    return SDLK_KP5;

  else if (key == "6")
    return SDLK_KP6;

  else if (key == "7")
    return SDLK_KP7;

  else if (key == "8")
    return SDLK_KP8;

  else if (key == "9")
    return SDLK_KP9;

  else if (key == ".")
    return SDLK_KP_PERIOD;

  else if (key == "/")
    return SDLK_KP_DIVIDE;

  else if (key == "*")
    return SDLK_KP_MULTIPLY;

  else if (key == "-")
    return SDLK_KP_MINUS;

  else if (key == "+")
    return SDLK_KP_PLUS;

  else if (key == "Enter")
    return SDLK_KP_ENTER;

  else if (key == "Equals")
    return SDLK_KP_EQUALS;

  else if (key == "Up")
    return SDLK_UP;

  else if (key == "Down")
    return SDLK_DOWN;

  else if (key == "Right")
    return SDLK_RIGHT;

  else if (key == "Left")
    return SDLK_LEFT;

  else if (key == "Insert")
    return SDLK_INSERT;

  else if (key == "Home")
    return SDLK_HOME;

  else if (key == "End")
    return SDLK_END;

  else if (key == "Page up")
    return SDLK_PAGEUP;

  else if (key == "Page down")
    return SDLK_PAGEDOWN;

  else if (key == "F1")
    return SDLK_F1;

  else if (key == "F2")
    return SDLK_F2;

  else if (key == "F3")
    return SDLK_F3;

  else if (key == "F4")
    return SDLK_F4;

  else if (key == "F5")
    return SDLK_F5;

  else if (key == "F6")
    return SDLK_F6;

  else if (key == "F7")
    return SDLK_F7;


  else if (key == "F8")
    return SDLK_F8;

  else if (key == "F9")
    return SDLK_F9;

  else if (key == "F10")
    return SDLK_F10;

  else if (key == "F11")
    return SDLK_F11;

  else if (key == "F12")
    return SDLK_F12;

  else if (key == "F13")
    return SDLK_F13;

  else if (key == "F14")
    return SDLK_F14;

  else if (key == "F15")
    return SDLK_F15;

  else if (key == "Right shift")
    return SDLK_RSHIFT;

  else if (key == "Left shift")
    return SDLK_LSHIFT;

  else if (key == "Right ctrl")
    return SDLK_RCTRL;

  else if (key == "Left ctrl")
    return SDLK_LCTRL;

  else if (key == "Right alt")
    return SDLK_RALT;

  else if (key == "Left alt")
    return SDLK_LALT;

  return SDLK_ESCAPE;
}

string
Board::convert (SDLKey key) const
{
  // En funktion som konverterar en SDLKey till
  // en textsträng, används i menyn för att kunna spara och
  // ladda från en fil samt för att visa vilka keybinds som redan
  // finns.

  switch (key)
    {
    case SDLK_BACKSPACE:
      return "Backspace";
      break;
    case SDLK_TAB:
      return "Tab";
      break;
    case SDLK_CLEAR:
      return "Clear";
      break;
    case SDLK_RETURN:
      return "Return";
      break;
    case SDLK_PAUSE:
      return "Pause";
      break;
    case SDLK_ESCAPE:
      return "Escape";
      break;
    case SDLK_SPACE:
      return "Space";
      break;
    case SDLK_EXCLAIM:
      return "!";
      break;
    case SDLK_QUOTEDBL:
      return "\"";
      break;
    case SDLK_HASH:
      return "#";
      break;
    case SDLK_DOLLAR:
      return "$";
      break;
    case SDLK_AMPERSAND:
      return "&";
      break;
    case SDLK_QUOTE:
      return "'";
      break;
    case SDLK_LEFTPAREN:
      return "(";
      break;
    case SDLK_RIGHTPAREN:
      return ")";
      break;
    case SDLK_ASTERISK:
      return "*";
      break;
    case SDLK_PLUS:
      return "+";
      break;
    case SDLK_COMMA:
      return ",";
      break;
    case SDLK_MINUS:
      return "-";
      break;
    case SDLK_PERIOD:
      return ".";
      break;
    case SDLK_SLASH:
      return "/";
      break;
    case SDLK_0:
      return "0";
      break;
    case SDLK_1:
      return "1";
      break;
    case SDLK_2:
      return "2";
      break;
    case SDLK_3:
      return "3";
      break;
    case SDLK_4:
      return "4";
      break;
    case SDLK_5:
      return "5";
      break;
    case SDLK_6:
      return "6";
      break;
    case SDLK_7:
      return "7";
      break;
    case SDLK_8:
      return "8";
      break;
    case SDLK_9:
      return "9";
      break;
    case SDLK_COLON:
      return ":";
      break;
    case SDLK_SEMICOLON:
      return "; Semicolon;";
      break;
    case SDLK_LESS:
      return "<";
      break;
    case SDLK_EQUALS:
      return ": =";
      break;
    case SDLK_GREATER:
      return ">";
      break;
    case SDLK_QUESTION:
      return "?";
      break;
    case SDLK_AT:
      return "@";
      break;
    case SDLK_LEFTBRACKET:
      return "[";
      break;
    case SDLK_BACKSLASH:
      return "\\";
      break;
    case SDLK_RIGHTBRACKET:
      return "";
      break;
    case SDLK_CARET:
      return "^";
      break;
    case SDLK_UNDERSCORE:
      return "_";
      break;
    case SDLK_BACKQUOTE:
      return "`";
      break;
    case SDLK_a:
      return "A";
      break;
    case SDLK_b:
      return "B";
      break;
    case SDLK_c:
      return "C";
      break;
    case SDLK_d:
      return "D";
      break;
    case SDLK_e:
      return "E";
      break;
    case SDLK_f:
      return "F";
      break;
    case SDLK_g:
      return "G";
      break;
    case SDLK_h:
      return "H";
      break;
    case SDLK_i:
      return "I";
      break;
    case SDLK_j:
      return "J";
      break;
    case SDLK_k:
      return "K";
      break;
    case SDLK_l:
      return "L";
      break;
    case SDLK_m:
      return "M";
      break;
    case SDLK_n:
      return "N";
      break;
    case SDLK_o:
      return "O";
      break;
    case SDLK_p:
      return "P";
      break;
    case SDLK_q:
      return "Q";
      break;
    case SDLK_r:
      return "R";
      break;
    case SDLK_s:
      return "S";
      break;
    case SDLK_t:
      return "T";
      break;
    case SDLK_u:
      return "U";
      break;
    case SDLK_v:
      return "V";
      break;
    case SDLK_w:
      return "W";
      break;
    case SDLK_x:
      return "X";
      break;
    case SDLK_y:
      return "Y";
      break;
    case SDLK_z:
      return "Z";
      break;
    case SDLK_DELETE:
      return "Delete";
      break;

    case SDLK_WORLD_0:
      return "world 0";
      break;
    case SDLK_WORLD_1:
      return "world 1";
      break;
    case SDLK_WORLD_2:
      return "world 2";
      break;
    case SDLK_WORLD_3:
      return "world 3";
      break;
    case SDLK_WORLD_4:
      return "world 4";
      break;
    case SDLK_WORLD_5:
      return "world 5";
      break;
    case SDLK_WORLD_6:
      return "world 6";
      break;
    case SDLK_WORLD_7:
      return "world 7";
      break;
    case SDLK_WORLD_8:
      return "world 8";
      break;
    case SDLK_WORLD_9:
      return "world 9";
      break;
    case SDLK_WORLD_10:
      return "world 10";
      break;
    case SDLK_WORLD_11:
      return "world 11";
      break;
    case SDLK_WORLD_12:
      return "world 12";
      break;
    case SDLK_WORLD_13:
      return "world 13";
      break;
    case SDLK_WORLD_14:
      return "world 14";
      break;
    case SDLK_WORLD_15:
      return "world 15";
      break;
    case SDLK_WORLD_16:
      return "world 16";
      break;
    case SDLK_WORLD_17:
      return "world 17";
      break;
    case SDLK_WORLD_18:
      return "world 18";
      break;
    case SDLK_WORLD_19:
      return "world 19";
      break;
    case SDLK_WORLD_20:
      return "world 20";
      break;
    case SDLK_WORLD_21:
      return "world 21";
      break;
    case SDLK_WORLD_22:
      return "world 22";
      break;
    case SDLK_WORLD_23:
      return "world 23";
      break;
    case SDLK_WORLD_24:
      return "world 24";
      break;
    case SDLK_WORLD_25:
      return "world 25";
      break;
    case SDLK_WORLD_26:
      return "world 26";
      break;
    case SDLK_WORLD_27:
      return "world 27";
      break;
    case SDLK_WORLD_28:
      return "world 28";
      break;
    case SDLK_WORLD_29:
      return "world 29";
      break;
    case SDLK_WORLD_30:
      return "world 30";
      break;
    case SDLK_WORLD_31:
      return "world 31";
      break;
    case SDLK_WORLD_32:
      return "world 32";
      break;
    case SDLK_WORLD_33:
      return "world 33";
      break;
    case SDLK_WORLD_34:
      return "world 34";
      break;
    case SDLK_WORLD_35:
      return "world 35";
      break;
    case SDLK_WORLD_36:
      return "world 36";
      break;
    case SDLK_WORLD_37:
      return "world 37";
      break;
    case SDLK_WORLD_38:
      return "world 38";
      break;
    case SDLK_WORLD_39:
      return "world 39";
      break;
    case SDLK_WORLD_40:
      return "world 40";
      break;
    case SDLK_WORLD_41:
      return "world 41";
      break;
    case SDLK_WORLD_42:
      return "world 42";
      break;
    case SDLK_WORLD_43:
      return "world 43";
      break;
    case SDLK_WORLD_44:
      return "world 44";
      break;
    case SDLK_WORLD_45:
      return "world 45";
      break;
    case SDLK_WORLD_46:
      return "world 46";
      break;
    case SDLK_WORLD_47:
      return "world 47";
      break;
    case SDLK_WORLD_48:
      return "world 48";
      break;
    case SDLK_WORLD_49:
      return "world 49";
      break;
    case SDLK_WORLD_50:
      return "world 50";
      break;
    case SDLK_WORLD_51:
      return "world 51";
      break;
    case SDLK_WORLD_52:
      return "world 52";
      break;
    case SDLK_WORLD_53:
      return "world 53";
      break;
    case SDLK_WORLD_54:
      return "world 54";
      break;
    case SDLK_WORLD_55:
      return "world 55";
      break;
    case SDLK_WORLD_56:
      return "world 56";
      break;
    case SDLK_WORLD_57:
      return "world 57";
      break;
    case SDLK_WORLD_58:
      return "world 58";
      break;
    case SDLK_WORLD_59:
      return "world 59";
      break;
    case SDLK_WORLD_60:
      return "world 60";
      break;
    case SDLK_WORLD_61:
      return "world 61";
      break;
    case SDLK_WORLD_62:
      return "world 62";
      break;
    case SDLK_WORLD_63:
      return "world 63";
      break;
    case SDLK_WORLD_64:
      return "world 64";
      break;
    case SDLK_WORLD_65:
      return "world 65";
      break;
    case SDLK_WORLD_66:
      return "world 66";
      break;
    case SDLK_WORLD_67:
      return "world 67";
      break;
    case SDLK_WORLD_68:
      return "world 68";
      break;
    case SDLK_WORLD_69:
      return "world 69";
      break;
    case SDLK_WORLD_70:
      return "world 70";
      break;
    case SDLK_WORLD_71:
      return "world 71";
      break;
    case SDLK_WORLD_72:
      return "world 72";
      break;
    case SDLK_WORLD_73:
      return "world 73";
      break;
    case SDLK_WORLD_74:
      return "world 74";
      break;
    case SDLK_WORLD_75:
      return "world 75";
      break;
    case SDLK_WORLD_76:
      return "world 76";
      break;
    case SDLK_WORLD_77:
      return "world 77";
      break;
    case SDLK_WORLD_78:
      return "world 78";
      break;
    case SDLK_WORLD_79:
      return "world 79";
      break;
    case SDLK_WORLD_80:
      return "world 80";
      break;
    case SDLK_WORLD_81:
      return "world 81";
      break;
    case SDLK_WORLD_82:
      return "world 82";
      break;
    case SDLK_WORLD_83:
      return "world 83";
      break;
    case SDLK_WORLD_84:
      return "world 84";
      break;
    case SDLK_WORLD_85:
      return "world 85";
      break;
    case SDLK_WORLD_86:
      return "world 86";
      break;
    case SDLK_WORLD_87:
      return "world 87";
      break;
    case SDLK_WORLD_88:
      return "world 88";
      break;
    case SDLK_WORLD_89:
      return "world 89";
      break;
    case SDLK_WORLD_90:
      return "world 90";
      break;
    case SDLK_WORLD_91:
      return "world 91";
      break;
    case SDLK_WORLD_92:
      return "world 92";
      break;
    case SDLK_WORLD_93:
      return "world 93";
      break;
    case SDLK_WORLD_94:
      return "world 94";
      break;
    case SDLK_WORLD_95:
      return "world 95";
      break;

    case SDLK_KP0:
      return "0";
      break;
    case SDLK_KP1:
      return "1";
      break;
    case SDLK_KP2:
      return "2";
      break;
    case SDLK_KP3:
      return "3";
      break;
    case SDLK_KP4:
      return "4";
      break;
    case SDLK_KP5:
      return "5";
      break;
    case SDLK_KP6:
      return "6";
      break;
    case SDLK_KP7:
      return "7";
      break;
    case SDLK_KP8:
      return "8";
      break;
    case SDLK_KP9:
      return "9";
      break;
    case SDLK_KP_PERIOD:
      return ".";
      break;
    case SDLK_KP_DIVIDE:
      return "/";
      break;
    case SDLK_KP_MULTIPLY:
      return "*";
      break;
    case SDLK_KP_MINUS:
      return "-";
      break;
    case SDLK_KP_PLUS:
      return "+";
      break;
    case SDLK_KP_ENTER:
      return "Enter";
      break;
    case SDLK_KP_EQUALS:
      return "Equals";
      break;

    case SDLK_UP:
      return "Up";
      break;
    case SDLK_DOWN:
      return "Down";
      break;
    case SDLK_RIGHT:
      return "Right";
      break;
    case SDLK_LEFT:
      return "Left";
      break;
    case SDLK_INSERT:
      return "Insert";
      break;
    case SDLK_HOME:
      return "Home";
      break;
    case SDLK_END:
      return "End";
      break;
    case SDLK_PAGEUP:
      return "Page up";
      break;
    case SDLK_PAGEDOWN:
      return "Page down";
      break;

    case SDLK_F1:
      return "F1";
      break;
    case SDLK_F2:
      return "F2";
      break;
    case SDLK_F3:
      return "F3";
      break;
    case SDLK_F4:
      return "F4";
      break;
    case SDLK_F5:
      return "F5";
      break;
    case SDLK_F6:
      return "F6";
      break;
    case SDLK_F7:
      return "F7";
      break;
    case SDLK_F8:
      return "F8";
      break;
    case SDLK_F9:
      return "F9";
      break;
    case SDLK_F10:
      return "F10";
      break;
    case SDLK_F11:
      return "F11";
      break;
    case SDLK_F12:
      return "F12";
      break;
    case SDLK_F13:
      return "F13";
      break;
    case SDLK_F14:
      return "F14";
      break;
    case SDLK_F15:
      return "F15";
      break;

    case SDLK_NUMLOCK:
      return "Numlock";
      break;
    case SDLK_CAPSLOCK:
      return "Caps lock";
      break;
    case SDLK_SCROLLOCK:
      return "Scroll lock";
      break;
    case SDLK_RSHIFT:
      return "Right shift";
      break;
    case SDLK_LSHIFT:
      return "Left shift";
      break;
    case SDLK_RCTRL:
      return "Right ctrl";
      break;
    case SDLK_LCTRL:
      return "Left ctrl";
      break;
    case SDLK_RALT:
      return "Right alt";
      break;
    case SDLK_LALT:
      return "Left alt";
      break;
    case SDLK_RMETA:
      return "Right meta";
      break;
    case SDLK_LMETA:
      return "Left meta";
      break;
    case SDLK_LSUPER:
      return "Left super";
      break; /* "Windows" keys */
    case SDLK_RSUPER:
      return "Right super";
      break;
    case SDLK_MODE:
      return "Alt gr";
      break;
    case SDLK_COMPOSE:
      return "Compose";
      break;

    case SDLK_HELP:
      return "Help";
      break;
    case SDLK_PRINT:
      return "Print screen";
      break;
    case SDLK_SYSREQ:
      return "Sys req";
      break;
    case SDLK_BREAK:
      return "Break";
      break;
    case SDLK_MENU:
      return "Menu";
      break;
    case SDLK_POWER:
      return "Power";
      break;
    case SDLK_EURO:
      return "Euro";
      break;
    case SDLK_UNDO:
      return "Undo";
      break;
    default:
      return "Ingen knapp";
    }
  return "ok";
}

Board::Board()
{
  // Dummy-konstruktor
}

Board::Board (int w, int h, int red, int green, int blue, int tema)
{
  // Konstruktor, de flesta tunga saker som bilder och ljud sparas
  // i Board så det är här allting laddas in samt här som den grafiska
  // bakgrunden till spelet skapas.

  square_size = 45;

  background.width = w;
  background.height = h;
  background.setBGColor (red, green, blue);
  background.Init ();

  // Tema sätts i inställningsmenyn, beroende på vilken man
  // väljer så laddas en annorlunda bild.
  if (tema == 1)
      pic = background.load ("tema1.png");
  if (tema == 2)
      pic = background.load ("tema2.png");
  if (tema == 3)
      pic = background.load ("tema3.png");
  if (tema == 4)
      pic = background.load ("tema4.png");

  // Skapar vektorer med default data som sedan skrivs
  // äver från load_settings() i menu.
  bindings.push_back (SDLK_RSHIFT);
  bindings.push_back (SDLK_LEFT);
  bindings.push_back (SDLK_RIGHT);
  bindings.push_back (SDLK_UP);
  bindings.push_back (SDLK_DOWN);

  bindings.push_back (SDLK_LSHIFT);
  bindings.push_back (SDLK_a);
  bindings.push_back (SDLK_d);
  bindings.push_back (SDLK_w);
  bindings.push_back (SDLK_s);

  bindings.push_back (SDLK_SPACE);
  bindings.push_back (SDLK_j);
  bindings.push_back (SDLK_l);
  bindings.push_back (SDLK_i);
  bindings.push_back (SDLK_k);

  bindings.push_back (SDLK_KP0);
  bindings.push_back (SDLK_KP3);
  bindings.push_back (SDLK_KP9);
  bindings.push_back (SDLK_KP5);
  bindings.push_back (SDLK_KP6);

  // Skapar den motsvarande text-vektorn.
  for (unsigned int i = 0; i < bindings.size (); i++)
    bindings_text.push_back (convert (bindings[i]));

  // Ladda in alla ljudfiler vi vill ha:
  audio.push_back(background.load_audio("play.wav"));
  audio.push_back(background.load_audio("firstblood.wav"));
  audio.push_back(background.load_audio("headshot.wav"));
  audio.push_back(background.load_audio("bomb.wav"));
  audio.push_back(background.load_audio("humiliation.wav"));
  audio.push_back(background.load_audio("multikill.wav"));
  audio.push_back(background.load_audio("powerup.wav"));

  // kills, kills_this_frame och humiliation används för att hålla koll
  // på hur många som dött för att avgöra vilket ljud som ska spelas.
  kills = 0;
  kills_this_frame = 0;
  humiliation = false;

  // Scoreboard?
  score.insert(pair<string, int> ("Red", 0));
  score.insert(pair<string, int> ("White", 0));
  score.insert(pair<string, int> ("Blue", 0));
  score.insert(pair<string, int> ("Green", 0));
}

Board::~Board()
{
  // Destruktor som städar upp alla datamedlemmar

  // Tar bort alla objekt ur mappar och vektorer
  clear();
  square_size = 0;
  kills = 0;
  kills_this_frame = 0;

  // Lämnar tillbaka minne för bilder
  background.free(pic);

  // Lämnar tillbaka minne för audio
  for (unsigned int i = 0; i < audio.size(); i++)
    background.free_audio(audio[i]);

  // Lämnar tillbaka minne för Class_SDL.
  background.~Class_SDL();
  bindings.clear();
  bindings_text.clear();
  score.clear();
}

void
Board::clear ()
{
  // Nollställer alla mappar och vektorer.
  indestructible_walls.clear ();
  dynamic_objects.clear ();
  power_ups.clear ();
  players.clear ();
  kills = 0;
}

void
Board::set_tema (int tema)
{
  // Används i menyn för att sätta vilken bild som ska laddas.

  // Lämna tillbaka minne för nuvarande bild
  background.free(pic);

  // Ladda den nya bilden
  if (tema == 1)
      pic = background.load ("tema1.png");
  else if (tema == 2)
      pic = background.load ("tema2.png");
  else if (tema == 3)
      pic = background.load ("tema3.png");
  else if (tema == 4)
      pic = background.load ("tema4.png");
}

void
Board::add_points(string color)
{
    for (vector<Object*>::iterator it = players.begin();
            it != players.end(); it++)
        if (dynamic_cast<Player*>(*it)->get_color() != color)
            score[dynamic_cast<Player*>(*it)->get_color()]++;
}

void
Board::reset_points()
{
  for (map<string, int>::iterator it = score.begin(); it != score.end(); it++)
    it->second = 0;
}

string
int_to_string (int str)
{
  stringstream out;
  out << str;
  return out.str ();
}

void
Board::display_points(int players)
{
  // Rita ut scoreboard

  if (players >= 2)
    {
      background.drawText
	("Red:", 24, 680, 50, 255, 255, 255);
      background.drawText
	(int_to_string (score["Red"]), 24, 865, 50, 255, 255, 255);

      background.drawText
	("White:", 24, 680, 100, 255, 255, 255);
      background.drawText
	(int_to_string (score["White"]), 24, 865, 100, 255, 255, 255);
    }

  if (players >= 3)
    {
      background.drawText
	("Blue:", 24, 680, 150, 255, 255, 255);
      background.drawText
	(int_to_string (score["Blue"]), 24, 865, 150, 255, 255, 255);
    }

  if (players == 4)
    {
      background.drawText
	("Green:", 24, 680, 200, 255, 255, 255);
      background.drawText
	(int_to_string (score["Green"]), 24, 865, 200, 255, 255, 255);
    }
}
