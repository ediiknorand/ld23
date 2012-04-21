#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

/* Initialization functions */
void engine_init_sdl()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
}

void engine_init_screen(int width, int height, int bpp, Uint32 flags)
{
  engine_screen.width = width;
  engine_screen.height = height;
  engine_screen.bpp = bpp;
  engine_screen.flags = flags;

  if(SDL_SetVideoMode(width, height, bpp, flags) < 0)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }
}

void engine_init_input()
{
  engine_input.up = 0;
  engine_input.down = 0;
  engine_input.left = 0;
  engine_input.right = 0;
}



/* Input Process */
void set_key(SDLKey k, unsigned char status)
{
  switch(k)
  {
  case SDLK_UP: engine_input.up = status; break;
  case SDLK_DOWN: engine_input.down = status; break;
  case SDLK_LEFT: engine_input.left = status; break;
  case SDLK_RIGHT: engine_input.right = status; break;
  }
}

void engine_input_process()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
    case SDL_KEYDOWN: set_key(event.key.keysym.sym, 1);
    case SDL_KEYUP: set_key(event.key.keysym.sym, 0);
    }
  }
}

/* Game runs */
int logic_refresh(Uint32 delta)
{
  engine_input_process();
  /* do something */
  return 1;
}

void render_refresh()
{
  /* do something */
}

void engine_run()
{
  int running;
  Uint32 now, before;

  running = 1;
  before = SDL_GetTicks();
  while(running)
  {
    now = SDL_GetTicks();
    running = logic_refresh(now - before);
    render_refresh();
    SDL_Delay(30); /* <- why not Vsynced? */
    before = now;
  }
}
