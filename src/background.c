#include <SDL/SDL.h>
#include "engine.h"
#include "background.h"

void background_load(char *filename)
{
  SDL_Surface *aux = SDL_LoadBMP(filename);
  background.img = SDL_DisplayFormat(aux);
  SDL_FreeSurface(aux);
  background.src_x = 0;
}

void background_unload()
{
  SDL_FreeSurface(background.img);
}

void background_draw(int x, Uint32 delta)
{
  int dx;

  background.src_x += x*(int)delta/30;
  background.src_x %= engine_screen.width;
  dx = background.img->w - background.src_x;
  engine_draw_sprite(background.img, background.src_x, 0, engine_screen.width, engine_screen.height, 0, 0);
  if(dx < engine_screen.width)
    engine_draw_sprite(background.img, 0, 0, engine_screen.width - dx, engine_screen.height, dx, 0);
}
