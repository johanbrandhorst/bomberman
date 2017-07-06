// Bomberman av Oskar Daniels, Robin Carlsson, David Enberg, Simon André
// och Johan Brandhorst

// Class_SDL.cc
// Datum: 08/12/11

#include "Class_SDL.h"
#include <string>

using namespace std;

Class_SDL::Class_SDL()
{
  // Dummy-konstuktor
}

Class_SDL::Class_SDL (int w, int h, int red, int green, int blue)
{
  // Skapa en bild med satt storlek och färg.
  width = w;
  height = h;
  setBGColor (red, green, blue);
}

Class_SDL::~Class_SDL ()
{
  // Frigör minne och stäng ner SDL.
  free (screen);
  Mix_FreeChunk (audio);
  Mix_CloseAudio ();
  TTF_Quit ();
  SDL_Quit ();
}

void
Class_SDL::Init ()
{
  // Funktion som körs efter konstruktorn, initierar
  // alla SDL-funktioner som behövs och gör så att SDL
  // ignorerar musrörelse som event-triggers.
  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
  TTF_Init ();

  screen = SDL_SetVideoMode (width, height, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption ("Bomberman", 0);

  // Inställningar för Ljudmixern.
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16;
  int audio_channels = 2;
  int audio_buffers = 4096;
  Mix_OpenAudio (audio_rate, audio_format, audio_channels, audio_buffers);
}

void
Class_SDL::start ()
{
  // Ritar ut skörmen, används i början av varje frame-loop.
  SDL_FillRect
    (screen, 0, SDL_MapRGB (screen->format, BGred, BGgreen, BGblue));
}

void
Class_SDL::end ()
{
  // Uppdaterar skärmen, används i slutet av varje frame-loop.
  SDL_Flip (screen);
}

Mix_Chunk*
Class_SDL::load_audio (const char* filename)
{
  // Laddar in en ljudfil och returnerar en Mix_Chunk* pekare.
  audio = Mix_LoadWAV (filename);
  return audio;
}

void
Class_SDL::play (Mix_Chunk* aud, int loop)
{
  // Spelar upp Mix_Chunk* objektet "aud" på en kanal som väljs av
  // SDL_mixer och loopar "loop" antal gånger
  Mix_PlayChannel (-1, aud, loop);
}

void
Class_SDL::free_audio (Mix_Chunk* aud)
{
  // Lämnare tillbaka minne.
  Mix_FreeChunk (aud);
}

SDL_Surface*
Class_SDL::load (const char* filename)
{
  // Laddar in en bild, optimerar bilden med dess alpha-channel
  // och returnerar den optimerade bilden och frigör minne
  // från den första bilden.
  SDL_Surface* image = 0;
  SDL_Surface* opt_image = 0;
  image = IMG_Load (filename);

  if (image != 0)
    {
      // Optimera bilden.
      opt_image = SDL_DisplayFormatAlpha (image);
      SDL_FreeSurface (image);
    }

  return opt_image;
}

void
Class_SDL::free (SDL_Surface* image)
{
  // Lämnar tillbaka minne.
  SDL_FreeSurface (image);
}
void
Class_SDL::drawSprite (SDL_Surface* image,
                       int sourceX, int sourceY,
                       int destX, int destY,
                       int width, int height)
{
  // Funktion som tar en del av en bild och kopierar den delen till
  // en ny bild med egendefinierad storlek och position.

  // Koordinater som kopieras ifrån
  SDL_Rect sourceRect;
  sourceRect.x = sourceX;
  sourceRect.y = sourceY;
  sourceRect.w = width;
  sourceRect.h = height;

  // Koordinater som klipps in i
  SDL_Rect destRect;
  destRect.x = destX;
  destRect.y = destY;
  destRect.w = width;
  destRect.h = height;

  SDL_BlitSurface (image, &sourceRect, screen, &destRect);
}

void
Class_SDL::setBGColor (int red, int green, int blue)
{
  // Funktion som ställer in bakgrundsfärg.
  BGred = red;
  BGgreen = green;
  BGblue = blue;
}

void
Class_SDL::drawText (string text, int size, int x, int y,
                     int Red, int Green, int Blue)
{
  // Ritar ut en text vid en given position, tar en string som
  // inparameter och gör om till en const char* array.

  TTF_Font* font = TTF_OpenFont ("ariblk.ttf", size);

  SDL_Color fColor = {Red, Green, Blue};

  const char* text2 = text.c_str ();

  // Blended är finaste text-utskriften i SDL_ttf, och används eftersom
  // text mest används i menyerna.
  SDL_Surface* textSurface = TTF_RenderText_Blended
    (font, text2, fColor);

  SDL_Rect textLocation = {x, y, 0, 0};

  SDL_BlitSurface (textSurface, 0, screen, &textLocation);

  // Efter att texten målats ut frigörs minnet för den temporära bilden.
  SDL_FreeSurface (textSurface);

  TTF_CloseFont (font);
}

